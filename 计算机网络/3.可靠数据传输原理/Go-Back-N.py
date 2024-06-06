import threading
import time
import random

# 模拟网络传输的参数
LOSS_PROBABILITY = 0.1  # 数据包丢失概率
DELAY = 1  # 网络延迟

class GoBackN:
    def __init__(self, window_size, total_packets):
        self.window_size = window_size
        self.total_packets = total_packets
        self.next_seq_num = 0
        self.base = 0
        self.lock = threading.Lock()
        self.ack_received = threading.Event()

    def send_packet(self, packet):
        if random.random() < LOSS_PROBABILITY:
            print(f"Packet {packet} lost")
        else:
            print(f"Packet {packet} sent")
            threading.Thread(target=self.receive_ack, args=(packet,)).start()

    def receive_ack(self, packet):
        time.sleep(DELAY)
        if random.random() < LOSS_PROBABILITY:
            print(f"ACK for packet {packet} lost")
        else:
            print(f"ACK for packet {packet} received")
            self.lock.acquire()
            self.base = packet + 1
            self.lock.release()
            self.ack_received.set()

    def send(self):
        while self.base < self.total_packets:
            while self.next_seq_num < self.base + self.window_size and self.next_seq_num < self.total_packets:
                self.send_packet(self.next_seq_num)
                self.next_seq_num += 1

            self.ack_received.wait()
            self.ack_received.clear()


gbn = GoBackN(window_size=4, total_packets=10)
gbn.send()
