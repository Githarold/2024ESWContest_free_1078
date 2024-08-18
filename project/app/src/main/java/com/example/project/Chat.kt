/**
 * Chat.kt
 * OpenAI API를 사용하여 칵테일 레시피를 추천하는 챗봇 기능을 구현한 액티비티
 */
package com.example.project

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import java.io.IOException
import android.view.inputmethod.EditorInfo
import android.view.KeyEvent
import android.widget.Toast
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.aallam.openai.api.BetaOpenAI
import com.aallam.openai.client.OpenAI
import com.aallam.openai.api.assistant.*
import com.aallam.openai.api.core.Role
import com.aallam.openai.api.core.Status
import com.aallam.openai.api.message.MessageContent
import com.aallam.openai.api.message.MessageRequest
import com.aallam.openai.api.model.ModelId
import com.aallam.openai.api.run.RunRequest
import kotlinx.coroutines.*
import java.io.OutputStream

class Chat : AppCompatActivity() {
    private var recyclerView: RecyclerView? = null
    private var tvWelcome: TextView? = null
    private var messageEdit: EditText? = null
    private var sendBtn: Button? = null
    private var messageList: MutableList<Message>? = null
    private var messageAdapter: MessageAdapter? = null
    private val REQUEST_ENABLE_BT = 1
    private val BLUETOOTH_PERMISSION_REQUEST_CODE = 100
    private lateinit var bluetoothAdapter: BluetoothAdapter
    private var isCommunicating = false
    private val handler = Handler(Looper.getMainLooper())
    private var dotsRunnable: Runnable? = null
    private var dots = ""
    private var recommendReason: String? = null
    private var currentCharIndex = 0
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_chat)
        recyclerView = findViewById(R.id.chat_recyclerView)
        tvWelcome = findViewById(R.id.tv_welcome)
        messageEdit = findViewById(R.id.message_edit)
        sendBtn = findViewById(R.id.send_btn)
        recyclerView!!.setHasFixedSize(true)
        val manager = LinearLayoutManager(this)
        manager.stackFromEnd = true
        recyclerView!!.layoutManager = manager
        messageList = ArrayList()
        messageAdapter = MessageAdapter(messageList!!, this)
        recyclerView!!.setAdapter(messageAdapter)

        // 블루투스 권한 요청
        if (ContextCompat.checkSelfPermission(
                this, Manifest.permission.BLUETOOTH_CONNECT) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                this, arrayOf(Manifest.permission.BLUETOOTH_CONNECT, Manifest.permission.BLUETOOTH_SCAN),
                BLUETOOTH_PERMISSION_REQUEST_CODE)
        }

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()

        // 블루투스 활성화 요청
        if (!bluetoothAdapter.isEnabled) {
            val enableBtIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT)
        }

        sendBtn!!.setOnClickListener {
            sendMessage()
        }

        messageEdit!!.setOnEditorActionListener { _, actionId, event ->
            if (actionId == EditorInfo.IME_ACTION_SEND ||
                (event?.action == KeyEvent.ACTION_DOWN && event.keyCode == KeyEvent.KEYCODE_ENTER)
            ) {
                sendMessage()
                return@setOnEditorActionListener true
            }
            return@setOnEditorActionListener false
        }

    }



    /**
     * 함수 정의 부분
     */

    // 메시지를 보내는 함수
    private fun sendMessage() {
        val question = messageEdit!!.getText().toString().trim { it <= ' ' }
        if (question.isEmpty()) {
            addToChat("아무것도 입력하지 않으셨네요. 어떤 칵테일을 드시고 싶은가요?", Message.SENT_BY_BOT, false)
            tvWelcome!!.visibility = View.GONE
        } else {
            addToChat(question, Message.SENT_BY_ME, false)
            startDotsAnimation() // 메시지를 보낼 때 애니메이션 시작
            CoroutineScope(Dispatchers.Main).launch {
                callAPI(question)
            }
            messageEdit!!.text.clear()
            tvWelcome!!.visibility = View.GONE
        }
    }


    // 채팅 메시지를 추가하는 함수
    private fun addToChat(message: String?, sentBy: String?, hasButton: Boolean = false) {
        runOnUiThread {
            messageList!!.add(Message(message, sentBy, hasButton))
            messageAdapter!!.notifyDataSetChanged()
            recyclerView!!.scrollToPosition(messageAdapter!!.getItemCount()-1)
        }
    }

    // 응답 메시지를 추가하는 함수
    private fun addResponse(response: String?, hasButton: Boolean = false) {
        stopDotsAnimation() // 응답을 추가할 때 기존 애니메이션 중지
        if (messageList!!.isNotEmpty() && messageList!!.last().sentBy == Message.SENT_BY_BOT) {
            messageList!!.removeAt(messageList!!.size - 1)
        }
        recommendReason = response
        addToChat("", Message.SENT_BY_BOT, hasButton) // 빈 문자열로 새로운 메시지 추가
        startTextAnimation() // 새로운 애니메이션 시작
    }

    // 애니메이션 시작 함수
    private fun startDotsAnimation() {
        dots = ""
        dotsRunnable = object : Runnable {
            override fun run() {
                dots += "."
                if (dots.length > 3) dots = ""
                updateDotsMessage()
                handler.postDelayed(this, 500)
            }
        }
        handler.post(dotsRunnable!!)
    }

    // 애니메이션 중지 함수
    private fun stopDotsAnimation() {
        handler.removeCallbacks(dotsRunnable!!)
        dotsRunnable = null
    }

    // 애니메이션 메시지 업데이트 함수
    private fun updateDotsMessage() {
        if (messageList!!.isNotEmpty() && messageList!!.last().sentBy == Message.SENT_BY_BOT) {
            messageList!!.last().message = dots
            messageAdapter!!.notifyItemChanged(messageList!!.size - 1, "payload")
            recyclerView!!.scrollToPosition(messageAdapter!!.itemCount - 1)
        }
    }

    private fun startTextAnimation() {
        currentCharIndex = 0
        dotsRunnable = object : Runnable {
            override fun run() {
                if (recommendReason != null && currentCharIndex < recommendReason!!.length) {
                    updateTextMessage(recommendReason!![currentCharIndex].toString())
                    currentCharIndex++
                    handler.postDelayed(this, 50)
                } else {
                    stopTextAnimation()
                }
            }
        }
        handler.post(dotsRunnable!!)
    }

    // 애니메이션 중지 함수
    private fun stopTextAnimation() {
        handler.removeCallbacks(dotsRunnable!!)
        dotsRunnable = null
    }

    // 애니메이션 메시지 업데이트 함수
    private fun updateTextMessage(char: String) {
        if (messageList!!.isNotEmpty() && messageList!!.last().sentBy == Message.SENT_BY_BOT) {
            messageList!!.last().message += char
            messageAdapter!!.notifyItemChanged(messageList!!.size - 1)
            recyclerView!!.post {
                val lastItemPosition = messageAdapter!!.itemCount - 1
                val lastVisibleItemPosition = (recyclerView!!.layoutManager as LinearLayoutManager).findLastVisibleItemPosition()

                if (lastItemPosition == lastVisibleItemPosition) {
                    recyclerView!!.scrollToPosition(lastItemPosition)
                }
            }
        }
    }



    // OpenAI API를 호출, 사용자 입력에 부합하는 칵테일을 추천한 뒤
    // addResponse 함수를 호출해 응답 메시지로 추가하는 함수
    @OptIn(BetaOpenAI::class)
    suspend fun callAPI(question: String?){
        messageList!!.add(Message("...", Message.SENT_BY_BOT, false))
        val openai = OpenAI( token = MY_SECRET_KEY)

        // Few-shot Learning을 위한 예시 입력 선언
        val exampleInputDict = mapOf(
            "Vodka" to 700, "Rum" to 700, "Gin" to 700, "Diluted Lemon Juice" to 1000,
            "Triple Sec" to 500, "Cranberry Juice" to 1000, "Grapefruit Juice" to 1000, "Orange Juice" to 800
        )

        val realInputDict = mapOf(
            "Vodka" to 1000, "Rum" to 700, "Gin" to 800, "Diluted Lemon Juice" to 800,
            "Triple Sec" to 500, "Cranberry Juice" to 900, "Grapefruit Juice" to 1000, "Orange Juice" to 800
        )

        val exampleUserMood1 = "오늘은 상쾌하고 열대의 풍미가 가득한 칵테일을 마시고 싶어요."
        val exampleGptResponse1 = "그런 날에는 '허리케인'을 추천드릴게요. 럼과 오렌지 주스가 어우러져 상쾌하고 달콤한 맛이 특징입니다. 열대 지방의 느낌을 가득 느끼실 수 있을 거예요.@[0,2,0,0,0,2,0,1]"

        val exampleUserMood2 = "오늘 뭔가 상큼하고 쌉쌀한 맛이 나는 칵테일이 생각나네요."
        val exampleGptResponse2 = "그렇다면 '그레이 하운드'를 추천드려요. 보드카와 자몽 주스가 어우러져 상큼하면서도 쌉쌀한 맛이 매력적인 칵테일입니다.@[2,0,0,0,0,0,0,3]"

        val exampleUserMood3 = "오늘은 좀 세련된 분위기의 칵테일을 마시고 싶어요."
        val exampleGptResponse3 = "세련된 분위기를 원하신다면 '코스모폴리탄'이 제격입니다. 보드카와 크랜베리 주스, 그리고 트리플 섹이 어우러져 우아한 맛을 느끼실 수 있습니다.@[2,0,0,1,0,0,0,1]"

        val exampleUserMood4 = "오늘은 강렬한 맛이 나는 칵테일이 마시고 싶어요."
        val exampleGptResponse4 = "그렇다면 '레드 데빌'을 추천드립니다. 보드카와 크랜베리 주스, 그리고 레몬 주스가 어우러져 강렬하고 상큼한 맛을 느끼실 수 있습니다.@[2,0,0,0,1,0,0,4]"

        val exampleUserMood5 = "오늘은 깔끔하면서도 우아한 칵테일을 마시고 싶어요."
        val exampleGptResponse5 = "그렇다면 '화이트 레이디'를 추천드려요. 진과 트리플 섹, 그리고 레몬 주스가 어우러져 깔끔하고 우아한 맛을 자랑하는 칵테일입니다.@[0,0,2,1,1,0,0,0]"

        val exampleUserMood6 = "친구들과 함께 즐길 수 있는 재미있는 칵테일이 필요해요."
        val exampleGptResponse6 = "그렇다면 '롱 비치 아이스티'를 추천드릴게요. 보드카, 럼, 진, 그리고 크랜베리 주스가 어우러져 강렬하면서도 상쾌한 맛을 느끼실 수 있습니다.@[1,1,1,1,1,0,0,0]"

        val exampleUserMood7 = "오늘은 상큼하고 달콤한 칵테일이 생각나요."
        val exampleGptResponse7 = "상큼하고 달콤한 맛을 원하신다면 '레몬 드롭 마티니'를 추천드립니다. 보드카와 레몬 주스, 그리고 트리플 섹이 어우러져 상큼하면서도 달콤한 맛이 일품인 칵테일입니다.@[2,0,0,1,1,0,0,0]"

        // AI 바텐더 Assistant 생성
        val batender = openai.assistant(
            request = AssistantRequest(
                name = "AI Bartender",
                model = ModelId("gpt-4o"),
                instructions = """
                    You are an AI bartender. First, receive the inventory as a dictionary named 'example_dict',
                    then consider the user's mood and preferences to recommend a cocktail.
                    Ensure that the total volume of ingredients does not exceed 250ml. Use a specific delimiter (@) to separate the cocktail recommendation from the recipe,
                    which should be provided in a structured list format, including two dictionaries:
                    one for the "Order" of ingredients and another for the "Integer" number of 30ml pumps required for each ingredient.
                """.trimIndent()
            )
        )

        // 대화를 관리할 Thread 생성
        val thread = openai.thread()
        println(thread.id)

        // 사용자 입력을 Thread에 전송
        openai.message(
            threadId = thread.id,
            request = MessageRequest(
                role = Role.User,
                content = question!!
            )
        )

        // Thread에 있는 메시지 확인
        val messages = openai.messages(thread.id)
        println("List of messages in the thread:")
        for (message in messages) {
            val textContent = message.content.first() as? MessageContent.Text ?: error("Expected MessageContent.Text")
            println(textContent.text.value)
        }


        // AI 바텐더에게 실행 요청
        val run = openai.createRun(
            threadId = thread.id,
            request = RunRequest(
                assistantId = batender.id,
                instructions = """
                            Ingredients in order: [Vodka, Rum, Gin, Triple Sec, Diluted Lemon Juice, Orange Juice, Grapefruit Juice, Cranberry Juice]

                            Example 1:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood1'
                            Output: $exampleGptResponse1
                            
                            Example 2:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood2'
                            Output: $exampleGptResponse2
                        
                            Example 3:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood3'
                            Output: $exampleGptResponse3
                        
                            Example 4:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood4'
                            Output: $exampleGptResponse4
                        
                            Example 5:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood5'
                            Output: $exampleGptResponse5
                            
                            Example 6:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood6'
                            Output: $exampleGptResponse6
                            
                            Example 7:
                            Input: Inventory - $exampleInputDict, Mood/Preference - '$exampleUserMood7'
                            Output: $exampleGptResponse7 
                            
                            You have to respond in Korean:
                            Input: Inventory - $realInputDict, Mood/Preference - '$question'
                            Output: 
                                            """.trimIndent())
        )

        // 실행 결과가 완료될 때까지 대기
        do {
            delay(1500)
            val retrievedRun = openai.getRun(threadId = thread.id, runId = run.id)
        } while (retrievedRun.status != Status.Completed)

        // AI 바텐더의 응답 메시지 처리
        val assistantMessages = openai.messages(thread.id)
        val message = assistantMessages[0]
        val textContent = message.content.first() as? MessageContent.Text ?: error("Expected MessageContent.Text")
        val messageText = textContent.text.value
        println(messageText)

        if (messageText.isNotEmpty()) {
            val parts = messageText.split("@")
            if (parts.size > 1) {
                val recommendReason = parts[0]

                recipeString = parts[1]
                Log.d("recipeString", recipeString!!)

                val list = recipeString!!.trim('[', ']').split(",").map { it.trim().toInt() }
                println(list)

                if (list.sum() > 7) {
                    println("recipe is more than 7")
                    addResponse(recommendReason, false)
                } else {

                    val recipe = list.joinToString(separator = "\n")
                    recipeString = "2\n\n$recipe\n\n0\n0\n0\n0\n0\n0\n0\n0"
                    Log.d("recipeString", recipeString!!)

                    addResponse(recommendReason, true)
                }
            } else {
                addResponse(messageText, false)
            }
        } else {
            addResponse("Err.. Try again", false)
        }


    }

    fun sendData(data: String) {
        synchronized(this) {
            if (isCommunicating) {
                Log.d("Bluetooth", "Communication is already in progress.")
                return@synchronized
            }
            isCommunicating = true
        }

        val communicationThread = Thread {
            try {
                val socket = BluetoothManager.getBluetoothSocket()
                if (socket == null || !socket.isConnected) {
                    runOnUiThread {
                        Toast.makeText(this, "Not connected to any device", Toast.LENGTH_SHORT).show()
                    }
                    return@Thread
                }

                val outStream: OutputStream = socket.outputStream
                outStream.write(data.toByteArray())
                Log.d("Bluetooth", "Data sent: $data")

                // 수신 버퍼 설정
                val buffer = ByteArray(1024)
                val inStream = socket.inputStream
                val bytesRead = inStream.read(buffer)
                if (bytesRead == -1) {
                    Log.d("Bluetooth", "Peer socket closed")
                } else {
                    val receivedData = String(buffer, 0, bytesRead)
                    Log.d("Bluetooth", "Data received: $receivedData")

                    runOnUiThread {
                        Toast.makeText(applicationContext, "Data received: $receivedData", Toast.LENGTH_SHORT).show()
                    }
                }

            } catch (e: IOException) {
                e.printStackTrace()
            } finally {
                synchronized(this) {
                    isCommunicating = false
                }
                Thread.currentThread().interrupt()
            }
        }
        communicationThread.start()
    }

    // 클래스 레벨에서 접근 가능한 객체 멤버 선언
    companion object {
        private const val MY_SECRET_KEY = ""
        var recipeString: String? = null
    }
}