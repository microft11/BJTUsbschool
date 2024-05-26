from socket import *

# 邮件内容配置
msg = "\r\n man!!! !!! what can i say????? manbaout !!!!!\r\n"
endMsg = "blbl\r\n.\r\n"
mailServer = "smtp.163.com"
fromAddress = "18810860817@163.com"
toAddress = "21281165@bjtu.edu.cn"
username = "18810860817@163.com"  # 用户名不需要编码
password = "RTPEWMXJBEMSZQKZ"  # 授权码

def send_command(command, expected_code):
    clientSocket.send(command.encode())
    response = clientSocket.recv(1024).decode()
    print(response)
    if response[:3] != expected_code:
        print(f'{expected_code} reply not received from server.')
    return response

# 创建客户端套接字并建立连接
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((mailServer, 25))
send_command('', '220')

# 发送 HELO 命令
send_command('HELO Alice\r\n', '250')

# 发送 AUTH LOGIN 命令并验证身份
send_command('AUTH LOGIN\r\n', '334')
send_command((username + '\r\n').encode('base64').strip(), '334')
send_command((password + '\r\n').encode('base64').strip(), '235')

# 发送邮件命令
send_command(f'MAIL FROM: <{fromAddress}>\r\n', '250')
send_command(f'RCPT TO: <{toAddress}>\r\n', '250')
send_command('DATA\r\n', '354')

# 编辑并发送邮件内容
subject = "man!!"
message = f'from: {fromAddress}\r\n' \
          f'to: {toAddress}\r\n' \
          f'subject: {subject}\r\n' \
          f'Content-Type: text/plain\r\n' \
          f'{msg}'

clientSocket.send(message.encode())
send_command(endMsg, '250')

# 断开连接
send_command('QUIT\r\n', '221')

clientSocket.close()

