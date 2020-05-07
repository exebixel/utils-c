#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "sqlconn.h"

// Inicia a conexão com o banco de dados mysql 
MYSQL *sqlConnect(){
    // cria uma referencia do banco, meio que vc ta iniciando ele...
    // dizendo que vai fazer a conexão
    MYSQL *conn = mysql_init(NULL);

    /* o mysql_real_connect como o nome sugere conecta de fato com o banco de dados
     * ele tem variaos parametros, sendo os principais a referencia da conexão (conn), 
     * o ip do banco (localhost), o nome do usuario (root), a senha (toor),
     * o que vem a seguir é porta, socket essas coisas, vai ler a documentação...
     * 
     * isso esta dentro da condição de um if para tratamento de erro
     * o mysql_real_connection retorna a referencia da conexão se a conexão for bem sucedida 
     * ou nulo (NULL) se a conexão for mal sucedida
     * como qualquer valor diferente de 0 (zero) e nulo (NULL) é interpretado como verdadeiro
     * isso é usado para o tratamento de erro da conexão ou seja 
     * se der errado exibe o erro no console (printf) e para a execução
     * se der certo retorna o ponteiro da conexão
     */
    char *user = "root";
    char *host = "localhost";
    char *password = "toor";
    char *database = "Corretor_provas";
    int port = 3306;
    char *unix_socket = NULL;
    long clientflag = 0;

    if (!mysql_real_connect(conn, host, user, password, 
                            database, port, 
                            unix_socket, clientflag))
    {
        printf("Erro ao conectar!!! \n%u %s \n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }
    else
    {
        return conn;
    }
}

// fecha a conexão com o banco de dados
void sqlClose(MYSQL *conn){
    mysql_close(conn);
}

int sqlCrud(char *sql)
{
    MYSQL *conn = sqlConnect();

    // testa se é uma conexão de "verdade", senão para a execução da função
    if (conn == NULL){
        return 0;
    } 
    
    if (mysql_query(conn, sql)){
        printf("Erro ao executar comando!!! \n%u %s \n", mysql_errno(conn), mysql_error(conn));
        sqlClose(conn);
        return 0;
    }

    sqlClose(conn);
    return 1;
}

// executa comando sql no banco de dados (mariadb)
MYSQL_RES *sqlSelect(char *sql){
    
    MYSQL *conn = sqlConnect();
    MYSQL_RES *res; // aqui é armasenado o retorno do comando sql
    // pelo menos eu acho que é por ai...

    // testa se é uma conexão de "verdade", senão para a execução da função
    if (conn == NULL){
        exit(1);
    }
    
    /*
     * mysql_query é a função que executa comandos do mysql
     * ela precisa da referencia (ponteiro) da conexão e do comando sql como argumentos
     * tambem está no if para tratamento de erro...
     * se der errado o comando exibe o erro no console a para a execução da função
     */
    if (mysql_query(conn, sql)){
        printf("Erro ao executar comando!!! \n%u %s \n", mysql_errno(conn), mysql_error(conn));
        sqlClose(conn);
        exit(1);
    }

    // armazena o retorno ou resultado do comando na variavel res que segnifica resultado
    res = mysql_store_result(conn);
    
    sqlClose(conn);

    /*
     * a variavel res tem o resultado do comando sql, mas esses dados não estão "tratados"
     * estão brutos e por motivos de que não se sabe o que será feito com esse resultado 
     * e para evitar um retrabalho de analize desses dados
     * ele é "entregue" bruto 
     */
    return res;
}
