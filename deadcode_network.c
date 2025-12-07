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
        conn->hostname = NULL;
        conn->protocol = NULL;
        conn->port = 0;
        
        if (hostname) {
            size_t hostname_len = strlen(hostname);
            if (hostname_len > 0 && hostname_len <= 255) {
                conn->hostname = (char*)malloc(hostname_len + 1);
                if (conn->hostname) {
                    strncpy(conn->hostname, hostname, hostname_len);
                    conn->hostname[hostname_len] = '\0';
                } else {
                    free(conn);
                    return NULL;
                }
            }
        }
        
        if (network_connection_validate_port(port)) {
            conn->port = port;
        }
        
        if (protocol) {
            size_t protocol_len = strlen(protocol);
            if (protocol_len > 0 && protocol_len <= 20) {
                conn->protocol = (char*)malloc(protocol_len + 1);
                if (conn->protocol) {
                    strncpy(conn->protocol, protocol, protocol_len);
                    conn->protocol[protocol_len] = '\0';
                } else {
                    if (conn->hostname) {
                        free(conn->hostname);
                    }
                    free(conn);
                    return NULL;
                }
            }
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
        size_t protocol_len = strlen(conn->protocol);
        size_t hostname_len = strlen(conn->hostname);
        if (protocol_len > 20 || hostname_len > 255) {
            return NULL;
        }
        size_t url_len = protocol_len + hostname_len + 20;
        char* url = (char*)malloc(url_len);
        if (url) {
            int result = snprintf(url, url_len, "%s://%s:%d", conn->protocol, conn->hostname, conn->port);
            if (result > 0 && (size_t)result < url_len) {
                return url;
            }
            free(url);
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
            conn->hostname = NULL;
        }
        size_t hostname_len = strlen(hostname);
        conn->hostname = (char*)malloc(hostname_len + 1);
        if (conn->hostname) {
            strncpy(conn->hostname, hostname, hostname_len);
            conn->hostname[hostname_len] = '\0';
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

