# 🍹 BartendAiRtist

![AI](https://github.com/Githarold/BartendAiRtist/assets/101968287/77cd479b-e9c5-4142-9f24-73aca56d9382)

BartendAiRtist에 오신 것을 환영합니다, 당신의 취향과 기분에 딱 맞춘 칵테일을 만들어 드립니다!

생성형 AI (Chat GPT API)를 활용한 BartendAiRtist는 당신의 칵테일 여정을 시작하도록 해줄 혁신적인 임베디드 시스템입니다. 안드로이드 앱에서 AI 바텐더와 대화를 나누고, 취향과 현재 기분을 말하기만 하면, 마법이 시작됩니다.

새로운 것을 원하든, 클래식한 칵테일을 원하든, 혹은 음료를 커스텀하고 싶든, BartendAiRtist는 개인화된 경험을 제공한 후, 즉석에서 완벽한 칵테일을 준비합니다.

## 📸 실물 사진

<img src="https://github.com/user-attachments/assets/1898ba7c-8bab-4310-af16-fe7fd42d0aa2" alt="KakaoTalk_20240904_160336996" width="40%">

## Table of Contents
- [🌟 Features](#-features)
- [📱 App Menu](#-app-menu)
- [🚀 Getting Started](#-getting-started)
- [📽️ Demo Results](#-demo-results)
- [📁 Project Structure](#-project-structure)
- [📞 Contact Us](#-contact-us)

## 🌟 Features

- **📲 개인 맞춤형 칵테일 추천:** 당신의 기분과 선호도를 말하며 당신만을 위한 칵테일 제안을 받아보세요.
- **🤖 자동 칵테일 준비:** 선택을 하면, 선택을 바탕으로 당신에게 완벽한 음료를 제공합니다.
- **💬 상호작용 챗 인터페이스:** 우리의 AI와 대화를 나누며 당신의 취향을 저격할 칵테일을 발견하세요.
- **👍 사용자 친화적인 안드로이드 애플리케이션:** 언제 어디서나 우리의 쉽게 사용할 수 있는 안드로이드 앱으로 BartendAiRtist에 접속하세요.

## 📱 App Menu

- **🔍 칵테일 추천 받기:** 현재 기분과 선호도를 바탕으로 AI가 제공하는 개인 맞춤형 칵테일 추천을 받아보세요.
- **📖 칵테일 리스트:** 클래식하고 인기 있는 칵테일의 리스트를 탐색하여 좋아하는 칵테을 찾아보세요.
- **✨ 칵테일 커스텀:** 원하는 재료와 양을 지정하여 나만의 독특한 칵테일을 만드세요.

## 🚀 Getting Started

BartendAiRtist를 통해 칵테일을 즐기고 싶다면 다음 단계를 따라주세요:

1. **앱 다운로드:** BartendAiRtist 애플리케이션을 스마트폰에 설치하세요.
2. **메뉴 선택:** 메뉴를 탭하여 칵테일 리스트, 칵테일 추천 받기, 칵테일 커스텀 중 선택하세요.
3. **AI 바텐더와 대화:** 개인 맞춤형 추천을 받거나 음료를 만들기 위해, 우리의 AI 바텐더와 대화하세요.
4. **선택하기:** AI 제안, 커스텀 옵션, 또는 칵테일 리스트에서 선호하는 칵테일을 선택하세요.
5. **모든 것을 잊고 취하기:** 스마트 바텐더가 칵테일을 준비하는 것을 지켜보세요. 건배!!!

## 📽️ Demo Results

아래는 BartendAiRtist의 시연 영상입니다. BartendAiRtist가 어떻게 작동하는지 확인해보세요!

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

여러분의 의견을 언제나 환영합니다! [harold3312@naver.com](mailto:harold3312@naver.com)으로 연락주세요.
