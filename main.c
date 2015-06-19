#include <stdio.h>
#include <mysql.h>

int main(){
  MYSQL *MySQLConRet;
  MYSQL *MySQLConnection = NULL;

  char *hostname = "localhost";
  char *user = "root";
  char password[20];
  char *db = "hedistest";

  MySQLConnection = mysql_init(NULL);

  printf("enter password: ");
  scanf("%s", password);

  MySQLConRet = mysql_real_connect(MySQLConnection, hostname, user, password, db, 0, NULL, 0);

  if(MySQLConRet == NULL){
    printf("fail\n");

    return 1;
  }

  printf("MySQL Connection Info: %s \n", mysql_get_host_info(MySQLConnection));
  printf("MySQL Client Info: %s \n", mysql_get_client_info());
  printf("MySQL Server Info: %s \n", mysql_get_server_info(MySQLConnection));

  return 0;
}
