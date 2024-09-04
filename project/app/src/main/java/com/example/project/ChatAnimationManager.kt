package com.example.project

import android.os.Handler
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class ChatAnimationManager(
    private val handler: Handler,
    private val recyclerView: RecyclerView,
    private val messageList: MutableList<Message>,
    private val messageAdapter: MessageAdapter
) {
    private var dotsRunnable: Runnable? = null
    private var currentCharIndex = 0
    private var dots = ""
    private var recommendReason: String? = null

    fun startDotsAnimation() {
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

    fun stopDotsAnimation() {
        handler.removeCallbacks(dotsRunnable!!)
        dotsRunnable = null
    }

    private fun updateDotsMessage() {
        if (messageList.isNotEmpty() && messageList.last().sentBy == Message.SENT_BY_BOT) {
            messageList.last().message = dots
            messageAdapter.notifyItemChanged(messageList.size - 1, "payload")
            recyclerView.scrollToPosition(messageAdapter.itemCount - 1)
        }
    }

    fun startTextAnimation(recommendReason: String?) {
        this.recommendReason = recommendReason
        currentCharIndex = 0
        dotsRunnable = object : Runnable {
            override fun run() {
                if (recommendReason != null && currentCharIndex < recommendReason.length) {
                    updateTextMessage(recommendReason[currentCharIndex].toString())
                    currentCharIndex++
                    handler.postDelayed(this, 50)
                } else {
                    stopTextAnimation()
                }
            }
        }
        handler.post(dotsRunnable!!)
    }

    fun stopTextAnimation() {
        handler.removeCallbacks(dotsRunnable!!)
        dotsRunnable = null
    }

    private fun updateTextMessage(char: String) {
        if (messageList.isNotEmpty() && messageList.last().sentBy == Message.SENT_BY_BOT) {
            messageList.last().message += char
            messageAdapter.notifyItemChanged(messageList.size - 1)
            recyclerView.post {
                val lastItemPosition = messageAdapter.itemCount - 1
                val lastVisibleItemPosition = (recyclerView.layoutManager as LinearLayoutManager).findLastVisibleItemPosition()

                if (lastItemPosition == lastVisibleItemPosition) {
                    recyclerView.scrollToPosition(lastItemPosition)
                }
            }
        }
    }
}
