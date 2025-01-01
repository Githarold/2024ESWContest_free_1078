# 🍹 BartendAiRtist

![AI](https://github.com/Githarold/BartendAiRtist/assets/101968287/77cd479b-e9c5-4142-9f24-73aca56d9382)

Welcome to BartendAiRtist, your personal cocktail assistant, crafting drinks tailored to your preferences and mood!

Powered by generative AI (Chat GPT API), BartendAiRtist is an innovative embedded system designed to elevate your cocktail experience. Simply chat with the AI bartender via the Android app, share your preferences and mood, and let the magic happen.

Whether you’re in the mood for something new, a classic cocktail, or a customized drink, BartendAiRtist provides a personalized experience and prepares the perfect cocktail on the spot.

## 📸 Real-life Photos

<img src="https://github.com/user-attachments/assets/1898ba7c-8bab-4310-af16-fe7fd42d0aa2" alt="KakaoTalk_20240904_160336996" width="40%">

## Table of Contents
- [🌟 Features](#-features)
- [📱 App Menu](#-app-menu)
- [🚀 Getting Started](#-getting-started)
- [📽️ Demo Results](#%EF%B8%8F-demo-results)
- [📁 Project Structure](#-project-structure)
- [📞 Contact Us](#-contact-us)

## 🌟 Features

- **📲 Personalized Cocktail Recommendations:** Get cocktail suggestions tailored to your mood and preferences.
- **🤖 Automated Cocktail Preparation:** Enjoy perfectly prepared drinks based on your selections.
- **💬 Interactive Chat Interface:** Chat with our AI to discover cocktails that match your taste.
- **👍 User-friendly Android Application:** Access BartendAiRtist through our easy-to-use Android app anytime, anywhere.

## 📱 App Menu

- **🔍 Get Cocktail Recommendations:** Receive personalized cocktail suggestions based on your current mood and preferences.
- **📖 Explore Cocktail List:** Browse a list of classic and popular cocktails to find your favorites.
- **✨ Customize Cocktails:** Specify ingredients and quantities to create your unique cocktail.

## 🚀 Getting Started

Follow these steps to enjoy cocktails with BartendAiRtist:

1. **Download the App:** Install the BartendAiRtist application on your smartphone.
2. **Choose a Menu:** Tap a menu to select from Cocktail List, Get Recommendations, or Customize Cocktails.
3. **Chat with the AI Bartender:** Interact with our AI bartender for personalized suggestions or drink creation.
4. **Make a Selection:** Choose your preferred cocktail from AI suggestions, custom options, or the Cocktail List.
5. **Watch the Magic:** Sit back and let the smart bartender prepare your drink. Cheers!

## 📽️ Demo Results

Here’s a demo of BartendAiRtist in action. See how it works!
[![BartendAiRtist 시연](https://img.youtube.com/vi/bvOnANFl0nA/0.jpg)](https://youtu.be/bvOnANFl0nA)

## 📁 Project Structure

### 🔌 Arduino
```
├── main
│   ├── main.ino
│   ├── motor_dc.cpp
│   ├── motor_dc.h
│   ├── motor_servo.cpp
│   ├── motor_servo.h
│   ├── motor_step.cpp
│   └── motor_step.h
└── testcode.py
```

### 📱 Android App
```
├── app
│   ├── build.gradle.kts
│   ├── proguard-rules.pro
│   └── src
│       ├── androidTest
│       │   └── java
│       │       └── com
│       │           └── example
│       │               └── project
│       │                   └── ExampleInstrumentedTest.kt
│       ├── main
│       │   ├── AndroidManifest.xml
│       │   ├── assets
│       │   │   ├── baybreeze.json
│       │   │   ├── cosmopolitan.json
│       │   │   ├── greyhound.json
│       │   │   ├── hurricane.json
│       │   │   ├── lemondropmartini.json
│       │   │   ├── longbeachicedtea.json
│       │   │   ├── planterspunch.json
│       │   │   ├── reddevil.json
│       │   │   ├── screwdriver.json
│       │   │   ├── seabreeze.json
│       │   │   └── whitelady.json
│       │   ├── java
│       │   │   └── com
│       │   │       └── example
│       │   │           └── project
│       │   │               ├── BluetoothManager.kt
│       │   │               ├── Chat.kt
│       │   │               ├── Choose.kt
│       │   │               ├── ChooseCustomMethod.kt
│       │   │               ├── Cocktail.kt
│       │   │               ├── CocktaillistAdapter.kt
│       │   │               ├── Custom.kt
│       │   │               ├── Dev.kt
│       │   │               ├── Ingredient.kt
│       │   │               ├── IngredientAdapter.kt
│       │   │               ├── MainActivity.kt
│       │   │               ├── Message.kt
│       │   │               ├── MessageAdapter.kt
│       │   │               ├── Pairing.kt
│       │   │               ├── SetBuildOrder.kt
│       │   │               ├── SetBuildOrderAdapter.kt
│       │   │               └── select.kt
│       │   └── res
│       │       ├── drawable
│       │       │   ├── baybreeze.png
│       │       │   ├── btn_background.xml
│       │       │   ├── btn_circle.xml
│       │       │   ├── cosmopolitan.png
│       │       │   ├── edit_background.xml
│       │       │   ├── greyhound.png
│       │       │   ├── hurricane.png
│       │       │   ├── ic_launcher_background.xml
│       │       │   ├── ic_launcher_foreground.xml
│       │       │   ├── lemondropmartini.png
│       │       │   ├── longbeachicedtea.png
│       │       │   ├── planterspunch.png
│       │       │   ├── reddevil.png
│       │       │   ├── screwdriver.png
│       │       │   ├── seabreeze.png
│       │       │   ├── ssam.png
│       │       │   ├── textview_background.xml
│       │       │   └── whitelady.png
│       │       ├── layout
│       │       │   ├── activity_chat.xml
│       │       │   ├── activity_choose.xml
│       │       │   ├── activity_choosecustommethod.xml
│       │       │   ├── activity_custom.xml
│       │       │   ├── activity_dev.xml
│       │       │   ├── activity_main.xml
│       │       │   ├── activity_pairing.xml
│       │       │   ├── activity_select.xml
│       │       │   ├── activity_setbuildorder.xml
│       │       │   ├── format_cocktail.xml
│       │       │   ├── format_setbuildorder.xml
│       │       │   ├── ingredient.xml
│       │       │   └── send.xml
│       │       ├── mipmap-anydpi
│       │       │   ├── ic_launcher.xml
│       │       │   └── ic_launcher_round.xml
│       │       ├── mipmap-hdpi
│       │       │   ├── ic_launcher.webp
│       │       │   └── ic_launcher_round.webp
│       │       ├── mipmap-mdpi
│       │       │   ├── ic_launcher.webp
│       │       │   └── ic_launcher_round.webp
│       │       ├── mipmap-xhdpi
│       │       │   ├── ic_launcher.webp
│       │       │   └── ic_launcher_round.webp
│       │       ├── mipmap-xxhdpi
│       │       │   ├── ic_launcher.webp
│       │       │   └── ic_launcher_round.webp
│       │       ├── mipmap-xxxhdpi
│       │       │   ├── ic_launcher.webp
│       │       │   └── ic_launcher_round.webp
│       │       ├── values
│       │       │   ├── colors.xml
│       │       │   ├── strings.xml
│       │       │   └── themes.xml
│       │       ├── values-night
│       │       │   └── themes.xml
│       │       └── xml
│       │           ├── backup_rules.xml
│       │           └── data_extraction_rules.xml
│       └── test
│           └── java
│               └── com
│                   └── example
│                       └── project
│                           └── ExampleUnitTest.kt
├── build.gradle.kts
├── gradle
│   ├── libs.versions.toml
│   └── wrapper
│       ├── gradle-wrapper.jar
│       └── gradle-wrapper.properties
├── gradle.properties
├── gradlew
├── gradlew.bat
└── settings.gradle.kts
```

### 📡 Communication Module
```
├── cocktail.json
├── parsing.py
├── processing.py
├── protocol.py
├── protocol2serial.py
├── protocol2serial1.py
├── server.py
└── write.py
```

## 📞 Contact Us

We always welcome your feedback! Feel free to contact us at [harold3312@naver.com](mailto:harold3312@naver.com).

## 📄 Acknowledgments

This app uses parts of the code from the [openai-kotlin](https://github.com/aallam/openai-kotlin) repository.
