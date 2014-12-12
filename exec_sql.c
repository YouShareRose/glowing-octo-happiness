#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "123456"
#define DATABASE "stu_info_sys"

/*a struct defines the table in database;*/
typedef struct {
    unsigned long field;
    unsigned long row;
} Table;

char * query_sql(const char *sql)
{
		int ret;
		MYSQL mysql;
		MYSQL_RES *res;
		MYSQL_ROW row;
		char *sqlresult;
		char *error = "SQL query error!";
		mysql_init(&mysql); 	  /*初始化连接句柄*/
		/*连接本地MySQL数据库，登录名为root，密码123456，数据库stu_info_sys*/
		if(mysql_real_connect(&mysql,HOST,USERNAME,PASSWORD,DATABASE,0,NULL,0)==NULL)
		{
			/*Sql connect failed*/
            printf("MySQL connect error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
            //mysql_close(&mysql);
            return error;
		}
		if(mysql_query(&mysql, sql)!=0)
		{
			/*Sql query failed*/
			printf("MySQL query error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
			return error;
		}
		res = mysql_store_result(&mysql);
		if(res == NULL)
		{
			/*Sql store result failed*/
			printf("MySQL store result error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
			mysql_close(&mysql);
			return error;
		}
		while(row = mysql_fetch_row(res))	/*逐行访问结果集中的记录*/
		{
			sqlresult = ((row[0]==NULL)&&(!strlen(row[0]))) ? "NULL" : row[0];
		}
		mysql_free_result(res);   /*释放结果集*/
		mysql_close(&mysql);   /*关闭数据库连接*/
		return sqlresult;
}		
		

#if 0	
		if(mysql_query(&mysql, sql)!=0) /*使用mysql_query()查询数据库*/
		{
			printf("Query table stu_info error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
		}
		if((res=mysql_store_result(&mysql))==NULL)/*使用mysql_store_result()初始化结果集*/
		{
			printf("MySQL store result error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
		}	
		//printf("Number of fields returned: %d\n",mysql_num_fields(res));  /*结果集中的列数*/
		while(row = mysql_fetch_row(res))	/*逐行访问结果集中的记录*/
		{
			sqlresult = ((row[0]==NULL)&&(!strlen(row[0]))) ? "NULL" : row[0];
		}
		mysql_free_result(res);   /*释放结果集*/
		mysql_close(&mysql);   /*关闭数据库连接*/
		return sqlresult;

printf("MySQL connect error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));



		if(mysql_query(&mysql, query2)!=0)
		{
			printf("Update table stu_info error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
			exit(1);
		}
		/*修改记录成功，调用mysql_affected_rows()返回表中受影响的行数*/
		printf("Update table stu_info success! %d row affected\n",mysql_affected_rows(&mysql));
		if(mysql_query(&mysql, query3)!=0)
		{
			printf("Delete table stu_info error! %d: %s\n",mysql_errno(&mysql),mysql_error(&mysql));
			exit(1);
		}
		/*删除记录成功，调用mysql_affected_rows()返回表中受影响的行数*/
		printf("Delete table stu_info success! %d row affected\n",mysql_affected_rows(&mysql));

		mysql_close(&mysql);   /*使用完毕，关闭数据库连接*/
		return 0;

}
#endif
