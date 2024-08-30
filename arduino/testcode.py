# -*- coding: utf-8 -*-

import serial
import time
import threading

# 시리얼 포트 설정 (라즈베리파이와 아두이노 간 통신)
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
time.sleep(2)  # 아두이노가 재시작할 시간을 주기 위해 추가

def generate_lists(step_input, linear_input):
    values, indices = [], []
    # 0이 아닌 원소와 그 인덱스를 저장
    for i, val in enumerate(step_input):
        if val != 0:
            values.append(val)
            indices.append(i)

    # 값에 따라 오름차순 정렬
    combined = sorted(zip(values, indices))
    values, indices = zip(*combined) if combined else ([], [])

    # disk_pre_rotation과 disk_rotation_list 생성
    disk_pre_rotation = [index + 1 for index in indices]
    disk_rotation_list = [
        disk_pre_rotation[i] - disk_pre_rotation[i - 1] if i > 0 else disk_pre_rotation[i] - 1
        for i in range(len(disk_pre_rotation))
    ]

    # disk_rotation_list의 모든 항목의 합을 0으로 만드는 음수값 추가
    total_sum = sum(disk_rotation_list)
    disk_rotation_list.append(-total_sum)

    # dispensor_activate_list 생성
    dispensor_activate_list = [linear_input[index] for index in indices]

    return disk_rotation_list, dispensor_activate_list

def send_data_to_arduino(dc_input, disk_rotation_list, dispensor_activate_list):
    data_string = f"{dc_input},{disk_rotation_list},{dispensor_activate_list}\n"
    ser.write(data_string.encode())
    print("Sent data:", data_string)

    while True:
        if ser.in_waiting > 0:
            response = ser.readline().decode('utf-8').strip()
            print("Received from Arduino:", response)
            if response == "9":  # 작업 완료 신호를 받으면 종료
                print("Finished")
                break
        
        time.sleep(1)

def main():
    try:
        while True:  
            step_input = list(map(int, input("Enter step input list (e.g., 3,0,4,1,0,0,0,2): ").split(',')))
            linear_input = list(map(int, input("Enter linear input list (e.g., 5,0,1,2,0,0,0,3): ").split(',')))
            dc_input = int(input("Enter DC input (0 or 1): "))  # 사용자로부터 0 또는 1 값을 직접 입력받음

            disk_rotation_list, dispensor_activate_list = generate_lists(step_input, linear_input)
            send_data_to_arduino(dc_input, disk_rotation_list, dispensor_activate_list)

            # 추가 명령을 받을지 여부를 묻기
            cont = input("Do you want to send another command? (y/n): ")
            if cont.lower() != 'y':
                break
        
    finally:
        ser.close()

if __name__ == '__main__':
    main()

