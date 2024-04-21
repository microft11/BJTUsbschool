# coding=utf-8

from http.server import BaseHTTPRequestHandler, HTTPServer

PORT_NUMBER = 8080

# 定义一个处理请求的类
class MyHandler(BaseHTTPRequestHandler):
    # 处理GET请求
    def do_GET(self):
        try:
            # 解析路径，映射到服务器上的相应文件
            path = self.translate_path(self.path)
            # 打开文件并发送响应
            with open(path, 'rb') as f:
                self.send_response(200)
                # 根据文件扩展名设置相应的MIME类型
                if path.endswith(".html"):
                    mimetype = 'text/html'
                elif path.endswith(".jpg"):
                    mimetype = 'image/jpeg'
                elif path.endswith(".gif"):
                    mimetype = 'image/gif'
                elif path.endswith(".js"):
                    mimetype = 'application/javascript'
                elif path.endswith(".css"):
                    mimetype = 'text/css'
                else:
                    mimetype = 'application/octet-stream' # 默认为二进制数据
                self.send_header('Content-type', mimetype)
                self.end_headers()
                # 发送文件内容
                self.wfile.write(f.read())
        except FileNotFoundError:
            # 文件不存在时发送404错误
            self.send_error(404, 'File Not Found: %s' % self.path)

    # 将URL路径转换为服务器文件系统路径
    def translate_path(self, path):
        # 根据实际情况修改路径映射规则
        path = path.split('?',1)[0]
        path = path.split('#',1)[0]
        path = path.strip()
        path = path.split('/')
        path = './html/' + '/'.join(path)
        return path

try:
    # 创建一个Web服务器并指定请求处理类
    server = HTTPServer(('127.0.0.1', PORT_NUMBER), MyHandler)
    print('Started httpserver on port ', PORT_NUMBER)

    # 持续监听来自客户端的请求
    server.serve_forever()

except KeyboardInterrupt:
    # 如果收到键盘中断信号，关闭服务器
    print('^C received, shutting down the web server')
    server.socket.close()
