#oluşturacağın PID takeoff testmode ve testmode(aralık)  adlı dört fonksiyon sayesinde drone üzerinde etkilerde bulunucaksın
#dronedan bilgileri alıp buna göre hareket etmen gerek 
#her bir fonksiyonun fiziksel olarak gereksinimleri olucak

"""
ESP32-CAM üzerinde wifi'ye bağlanıyorken denemesi gereken wifi ağlarının listesini sdcard içerisindeki bir dosyaya kaydedebilirsin
"""

# *****inputs*****
import socket 
# *****inputs end*****

# ****support functions****
def socket_send(host_ip,data):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    port =  5394
    try:
        # Connect to the server
        sock.connect((server_ip, server_port))
        print("Connected to server")

        # Send data to the server
        sock.sendall(data.encode())
        print("Data sent:", data)

        # Receive data from the server (optional)
        received_data = sock.recv(1024)
        print("Received data:", received_data.decode())

    finally:
        # Close the socket
        sock.close()
        print("Socket closed")
# ****support functions end****
def PID():
    #LCD ekran, pid değerleri için butonların bağlı olması gerekiyor 
    #lcd ekran üzerinden pid değerlerini görebilicekler ve pid değerlerini butonlar ile değiştirip sürekli program yüklemeden pid ayarlaması yapabilecekler
    #pid değerleri hem bilgisayar üzerinden ayarlanabilir hemde fiziksel olarak butonlarla ayarlanabilir olucaktır
    #kullanıcı pid değerlerini wifi üzerinden stm32'ye aktarman lazım 
    #önce kullanıcıdan pid değerlerini al 
    #sonra bunları socket kullanarak esp32'ye ilet | esp32 ip adresini kullanıcıdan iste veya bir txt dosyasından çek 


    print("Pid değerlerini giriniz \n")
    Kp = str(input("Kp : "))
    Kd = str(input("Kd : "))
    Ki = str(input("Ki : "))
    esp32_ip_adress = str(input("ESP32-CAM ip adress: "))

    final_data = f"PIDVALUES|||{Kp},{Kd},{Ki}\n"
    socket_send(esp32_ip_address,final_data)
    
def takeoff():
    #fiziksel olarak drone'un bir yere bağlanmış ve dronedan uzak olunması beklenecek 
    #pid ayarlaması yapılması gerekiyor çünkü her türlü drone sağ sol yapacaktır bu tarz bi durumda pid drone'u doğru pozisyona getiricek 
    is_drone_tied  = int(input("Drone yere bağlı mı ?(1,0) : "))
    if is_drone_tied == 1:
        esp32_ip_adress = str(input("ESP32-CAM ip adress: "))

        final_data = f"TAKEOFF|||\n"
        socket_send(esp32_ip_adress,final_data)
    else:
        print("fonksiyon çalıştırılmadı. Drone'u bağlayın !")
        

def testmode():
    #testmode 1 motorları 1150 hızında çalıştırıp program iletişim kurabiliyor mu bunu denemek için var
    #pervanelerin çıkarılmış olması istenecektir
    is_props_removed = input("Pervaneler çıkarıldı mı ?(1,0) : ")
    if is_props_removed == 1:
        esp32_ip_adress = str(input("ESP32-CAM ip adress: "))

        final_data = f"TESTMODE1|||\n"
        socket_send(esp32_ip_adress,final_data)
    else:
        print("fonksiyon çalıştırılmadı. Pervaneleri çıkarın !")

def testmode2():
    #testmode2 her bir motoru ayrı ayrı veya aynı anda istenilen hızda çalıştırmak için bulunuyor
    #pervanelerin çıkarılmış olması istenecektir
    is_props_removed = input("Pervaneler çıkarıldı mı ?(1,0) :")
    if is_props_removed == 1:
        motor_number = int(input("Hangi motoru çalıştırıcaksınız (sol_arka : 1, sol_ön : 2, sağ_arka : 3, sağ_ön : 4)"))
        motor_speed =  int(input("Motor hızı kaç olsun (1000-2000) : "))
        esp32_ip_adress = str(input("ESP32-CAM ip adress: "))

        final_data = f"TESTMODE2|||{motor_number},{motor_speed}\n"
        socket_send(esp32_ip_adress,final_data)
    else:
        print("fonksiyon çalıştırılmadı. Pervaneleri çıkarın !")
