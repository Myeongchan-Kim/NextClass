# -*- coding: utf-8 -*-

import socket
import sys
import threading


def listen_to_server(conn):
    while True:
        try:
            data = conn.recv(buffer_size)
            while data:
                print >>sys.stderr, "%s" % data
                data = ""

        except socket.error:
            print socket.error.message
            return


def input_send(sock):
    # Connect the socket to the port on the server given by the caller
    print >>sys.stderr, 'connecting to %s port %s' % server_address
    message = ""

    while True:
        try:
            message = raw_input("->")
            if message == "":
                continue

            print >>sys.stderr, 'sending "%s"' % message
            sock.sendall(message + "")
            if message == 'exit':
                print >>sys.stderr, "Socket close"
                sock.close()
                return

        except socket.error:
            print socket.error.message
            break


if __name__ == '__main__':
    address = ""
    port_num = ""
    welcome_str = '''
Welcome! Guest.
This is Paul-Kim's multiple chatting application.
public server (seoul, South Korea) is 'seoul'
If you want exit chatting, type 'exit'
enjoy your chat!
    '''
    print welcome_str
    while not address:
        address = raw_input("Server address (ex 127.0.0.1, 'seoul') : ")
        if address == 'seoul':
            address = '52.79.77.102'
            port_num = 10000

    while not port_num:
        port_num = raw_input("port number : ")
    server_address = (address, int(port_num))
    buffer_size = 65536

    # Create a TCP/IP socket
    try:
        print "connect to %s(%s)..." % (address, port_num)
        tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        tcp_sock.connect(server_address)
        listen_th = threading.Thread(target=listen_to_server, args=(tcp_sock,))
        listen_th.start()
        input_send(tcp_sock)
    except socket.error:
        print >>sys.stderr, socket.error.message

    print 'Good, bye.'
