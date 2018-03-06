#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

MYSQL connection;

void finishWithError()
{
    fprintf(stderr, "%s\n", mysql_error(&connection));
    mysql_close(&connection);
    exit(1);
}

void connectDB(void) {
    if (mysql_init(&connection) == NULL) {
        printf("Erro ao iniciar a conexão com o servidor MySQL!\n");
        exit(1);
    }

    if (mysql_real_connect(&connection, "localhost", "root", "odk97004519lmsbr", NULL, 3306, NULL, 0)) {
        printf("Conexão com o servidor MySQL iniciada com sucesso.\n");
    }
    else {
        printf("Falha ao conectar no servidor MySQL!\n");
        printf("MySQL error message: %s\n", mysql_error(&connection));
        exit(1);
    }
};

void createTables (void);

void createTables(void) {
    if (mysql_query(&connection, "DROP TABLE IF EXISTS Detalhes")) {
        finishWithError();
    }
    if(mysql_query(&connection,
                   "CREATE TABLE IF NOT EXISTS Detalhes (\n"
                           "    id int(11) NOT NULL,\n"
                           "    username varchar(255) NOT NULL,\n"
                           "    first_name varchar(255) NOT NULL,\n"
                           "    last_name varchar(255) NOT NULL,\n"
                           "    email varchar(255) NOT NULL,\n"
                           "    password varchar(32) NOT NULL,\n"
                           "    sign_up_date date NOT NULL,\n"
                           "    activated enum('0','1') NOT NULL,\n"
                           "    PRIMARY KEY (id)\n"
                           ") ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;") == 0) {
        printf("Table created. \n");
    }
    else {
        printf("Table creation failed. ");
        printf("MySQL error message: %s\n", mysql_error(&connection));
        exit(1);
    }
}

void createDB (void);

void createDB(void) {
    if(mysql_query(&connection, "USE Clientes") == 0) {
        printf("Banco de dados já existe.\n");
    } else {
        if (mysql_query(&connection, "CREATE DATABASE Clientes") == 0) {

            printf("Banco de dados criado com sucesso.\n");
            createTables();
        }
        else {
            printf("Falha na criação do banco de dados. ");
            printf("MySQL error message: %s\n", mysql_error(&connection));
            exit(1);
        }

    }
    mysql_close(&connection);
}

int main(int argc, char **argv) {
    int sysSize = sizeof(int);
    printf("int size is: %d bytes\n", sysSize);
    printf("MySQL client version: %s\n", mysql_get_client_info());

    connectDB();

    createDB();

    return 0;
}