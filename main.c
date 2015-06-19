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

  int mysqlStatus = 0;
  MYSQL_RES *mysqlResult = NULL;

  if(mysqlResult){
    mysql_free_result(mysqlResult);
    mysqlResult = NULL;
  }

  MYSQL_ROW mysqlRow;
  MYSQL_FIELD *mysqlFields;
  my_ulonglong numRows;
  unsigned int numFields;

  char *sqlSelStatement = "select * from user";

  mysqlStatus = mysql_query(MySQLConnection, sqlSelStatement);

  if(mysqlStatus){
    printf((char *)mysql_error(MySQLConnection));

    return 1;
  }

  mysqlResult = mysql_store_result(MySQLConnection);

  if(mysqlResult){
    numRows = mysql_num_rows(mysqlResult);

    numFields = mysql_field_count(MySQLConnection);

    numFields = mysql_num_fields(mysqlResult);

    printf("Number of rows=%u  Number of fields=%u \n",numRows,numFields);
  }else{
    printf("Result set is empty\n");
  }

  mysqlFields = mysql_fetch_fields(mysqlResult);

  for(int i = 0; i < numFields; i++){
    printf("%s\t", mysqlFields[i].name);
  }

  printf("\n");

  while(mysqlRow = mysql_fetch_row(mysqlResult)){
    for(int i = 0; i < numFields; i++){
      printf("%s\t", mysqlRow[i] ? mysqlRow[i] : "NULL");
    }

    printf("\n");
  }

  if(mysqlResult){
    mysql_free_result(mysqlResult);

    mysqlResult = NULL;
  }

  mysql_close(MySQLConnection);

  return 0;
}
