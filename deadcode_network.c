// Dead Code - Network Utility Class
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* hostname;
    int port;
    char* protocol;
} NetworkConnection;

NetworkConnection* network_connection_create(const char* hostname, int port, const char* protocol) {
    NetworkConnection* conn = (NetworkConnection*)malloc(sizeof(NetworkConnection));
    if (conn) {
        if (hostname) {
            conn->hostname = (char*)malloc(strlen(hostname) + 1);
            if (conn->hostname) {
                strcpy(conn->hostname, hostname);
            }
        } else {
            conn->hostname = NULL;
        }
        
        conn->port = port;
        
        if (protocol) {
            conn->protocol = (char*)malloc(strlen(protocol) + 1);
            if (conn->protocol) {
                strcpy(conn->protocol, protocol);
            }
        } else {
            conn->protocol = NULL;
        }
    }
    return conn;
}

int network_connection_validate_port(int port) {
    return (port > 0 && port <= 65535);
}

int network_connection_validate_hostname(const char* hostname) {
    if (hostname && strlen(hostname) > 0 && strlen(hostname) <= 255) {
        for (int i = 0; hostname[i] != '\0'; i++) {
            char c = hostname[i];
            if (!((c >= 'a' && c <= 'z') || 
                  (c >= 'A' && c <= 'Z') || 
                  (c >= '0' && c <= '9') || 
                  c == '.' || c == '-')) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

char* network_connection_build_url(NetworkConnection* conn) {
    if (conn && conn->hostname && conn->protocol) {
        int url_len = strlen(conn->protocol) + strlen(conn->hostname) + 20;
        char* url = (char*)malloc(url_len);
        if (url) {
            sprintf(url, "%s://%s:%d", conn->protocol, conn->hostname, conn->port);
            return url;
        }
    }
    return NULL;
}

void network_connection_set_port(NetworkConnection* conn, int port) {
    if (conn && network_connection_validate_port(port)) {
        conn->port = port;
    }
}

void network_connection_set_hostname(NetworkConnection* conn, const char* hostname) {
    if (conn && hostname && network_connection_validate_hostname(hostname)) {
        if (conn->hostname) {
            free(conn->hostname);
        }
        conn->hostname = (char*)malloc(strlen(hostname) + 1);
        if (conn->hostname) {
            strcpy(conn->hostname, hostname);
        }
    }
}

int network_connection_get_port(NetworkConnection* conn) {
    if (conn) {
        return conn->port;
    }
    return -1;
}

const char* network_connection_get_hostname(NetworkConnection* conn) {
    if (conn) {
        return conn->hostname;
    }
    return NULL;
}

void network_connection_destroy(NetworkConnection* conn) {
    if (conn) {
        if (conn->hostname) {
            free(conn->hostname);
        }
        if (conn->protocol) {
            free(conn->protocol);
        }
        free(conn);
    }
}

