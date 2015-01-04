 /* 
 * 文件名称：admin_win.c
 * 功能描述：构建管理员查询GUI界面，处理管理员用户的各种查询操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#define _N(str) g_locale_to_utf8(str, -1, NULL,NULL,NULL)

enum
{
		STU_ID = 0,
		STU_NAME,
		STU_GENDER,
		STU_BIRTH,
		STU_DEPART,
		STU_CLASS,
		ADMIN_COLUM_NUM
};
extern Table adm_res_tab;

int show_teacher_window()
{
		GladeXML *AdminWinXML;
		GtkWidget *admin_window, *exit_button;
		GtkWidget *treeview;      /*树视图*/
		GtkTreeIter iter;           /*迭代器*/
		GtkCellRenderer* renderer;  /*渲染器*/
		GtkTreeModel *store;      /*树模式*/
		char *sqlresult;
		MYSQL_ROW row;
		unsigned int i=0;
		
		gtk_init(&argc,&argv);
		AdminWinXML = glade_xml_new("ui/admin_win.glade", NULL, NULL);
		admin_window = glade_xml_get_widget(AdminWinXML, "window1");
		glade_xml_signal_autoconnect(AdminWinXML);
		treeview = glade_xml_get_widget(AdminWinXML, "treeview");
		/*定义渲染器，定义视图中的列，设置各列的数据均为text*/
		renderer = gtk_cell_renderer_text_new();
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 学  号 "), renderer, "text", STU_ID, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 姓  名 "), renderer, "text", STU_NAME, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 性  别 "), renderer, "text", STU_GENDER, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 出生日期 "), renderer, "text", STU_BIRTH, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 院  系 "), renderer, "text", STU_DEPART, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 班  级 "), renderer, "text", STU_CLASS, NULL);
		/*设置树模式中各列的数据类型*/
		store = GTK_TREE_MODEL(gtk_list_store_new(ADMIN_COLUM_NUM,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING));
		gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), store);
		/*向模式中插入数据*/
		for(i=0; i<adm_res_tab.row; i++)
		{
			row = mysql_fetch_row(adm_res_tab.res)
			gtk_list_store_append(GTK_LIST_STORE(store), &iter);   /*获取插入的位置*/
			gtk_list_store_set(GTK_LIST_STORE(store),&iter,STU_ID,row[STU_ID],STU_NAME,row[STU_NAME],STU_GENDER,row[STU_GENDER],STU_BIRTH,row[STU_BIRTH],STU_DEPART,ROW[STU_DEPART],STU_CLASS,row[STU_CLASS],-1);
		}
		g_object_unref(store);
		/*为界面添加信号*/
		exit_button = glade_xml_get_widget(AdminWinXML, "exit_button");
		g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(gtk_main_quit),admin_window);
		g_signal_connect(G_OBJECT(admin_window),"destroy",G_CALLBACK(gtk_main_quit),admin_window);
		gtk_widget_show_all(admin_window);
		gtk_main();
		return 0;
}
