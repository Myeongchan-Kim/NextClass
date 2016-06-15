# -*- coding: utf-8 -*-

import socket
import sys
import threading
import datetime


def check_http(request):
    # print request
    tmp = request.split("\n")
    print tmp[0]
    tmp = tmp[0].split("/")
    if len(tmp) > 1 and tmp[1].strip()[-4:] == "HTTP":
        return True
    return False


def make_default_response():
    datetime_now = datetime.datetime.now()
    datetime_string = datetime_now.strftime('%a, %d %b %Y %H:%M:%S GMT')

    http_contents = '''
<html><head><title>MCDantalk</title>
</head><body>
Sorry, This server is only for MC_dantalk program.<br />
If you want use this server, follow this : <a href="https://github.com/Paul-Kim/MCDanTalk">MC dantalk Git hub</a><br/>
thank you.<br />
</body>
</html>
'''

    http_header = '''
HTTP/1.1 200 OK
Date: %s
Server: MCDantalk server
X-Powered-By: Paul-Kim
Last-Modified: %s
Cache-Control: no-store, no-cache, must-revalidate
Content-Length: %d
Content-Type: text/html

''' % (datetime_string, datetime_string, len(http_contents))

    return http_header + http_contents


def echo_you_said(conn, client):
    response_string = ""
    while True:
        try:
            data = conn.recv(buffer_size)
            while True:
                response_string += data
                if len(data) < buffer_size:
                    break

            if response_string == 'exit':
                for g_conn in connection_list:
                    g_conn[0].sendall("" + "%s(%s)" % client + "exit server.")
                conn.close()
                break

            if check_http(response_string):
                response_string = make_default_response()
                conn.sendall(response_string)
                conn.close()
                break

            print >>sys.stderr, 'received "%s"' % data
            for g_conn in connection_list:
                if g_conn[0] == conn:
                    conn.sendall("You: %s " % response_string)
                else:
                    g_conn[0].sendall("" + "%s(%s)" % client + ": " + response_string)
            response_string = ""
        except socket.error:
            print socket.error.message
            break
    print >>sys.stderr, "client ", client[1], "'s connection is closed."
    connection_list.remove((conn, client))


# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the address given on the command line
server_name = '0.0.0.0'
server_address = (server_name, 10000)
sock.bind(server_address)
buffer_size = 65536
connection_list = []
sock.listen(1)
print >>sys.stderr, 'starting up on %s port %s' % server_address

while True:
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    print >>sys.stderr, 'client connected:', client_address
    print >>sys.stderr, connection, client_address
    connection_list.append((connection, client_address))
    th = threading.Thread(target=echo_you_said, args=(connection, client_address))
    th.start()
