#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#define _N(str) g_locale_to_utf8(str, -1, NULL,NULL,NULL)

GtkWidget *login_window;
GtkWidget *name_entry, *pwd_entry;
char  identity = 1;

void dialog_exit(GtkWidget * widget, gpointer data)
{
		gtk_widget_destroy((GtkWidget *)data);
		gtk_entry_set_text(GTK_ENTRY(name_entry), "");
		gtk_entry_set_text(GTK_ENTRY(pwd_entry), "");	
}

void error_notify()
{
		GladeXML *error_notify;
		GtkWidget *dialog,*button;
		error_notify = glade_xml_new("ui/error.glade", NULL, NULL);
		dialog = glade_xml_get_widget(error_notify, "error_notify_dialog");
		button = glade_xml_get_widget(error_notify, "ok_button");
		glade_xml_signal_autoconnect(error_notify);
		g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(dialog_exit), dialog);
		gtk_widget_show_all(dialog);
}

void on_login_button_clicked(GtkWidget * widget, gpointer data)
{
		char name[10];
		char password[10];
		char *password_in_db;
		char *sql = NULL;

		/*获取用户输入的用户名和密码*/
		strcpy(name, gtk_entry_get_text(GTK_ENTRY(name_entry)));
		strcpy(password, gtk_entry_get_text(GTK_ENTRY(pwd_entry)));
		sql = (char *)malloc(sizeof(char)*100);
		if(identity == 1) /*学生登录，用户名为8位字符串，密码为6位字符串*/
		{
			strcpy(sql, "select stu_passwd from student where stu_id=");
			strcat(sql, name);
			puts(sql);
			password_in_db = (char *)query_sql(sql);
			puts(password_in_db);
			if(!strcmp(password,password_in_db))
			{
				printf("student login!\n");
				gtk_widget_hide_all(login_window);
				show_student_window();
			}
			else
			{
				error_notify();
			}
		}
		else if(identity == 2)
		{
			strcpy(sql, "select tea_passwd from teacher where tea_id=");
			strcat(sql, name);
			password_in_db = (char *)query_sql(sql);
			if(!strcmp(password,password_in_db))
			{
				printf("teacher login!\n");
				gtk_widget_hide_all(login_window);
				show_teacher_window();
			}
			else
			{
				error_notify();
			}
		}
		else if(identity==3 && !strncmp(name,"admin",5) && !strncmp(password,"admin",5)) /*管理员登录，管理员只有一个账户，用户名和密码均为admin*/
		{
			printf("admin login!\n");
			gtk_widget_hide_all(login_window);
			show_admin_window();
		}
		else
		{
			error_notify();
		}
}

void radiobutton_clicked(GtkWidget * widget, gpointer data)
{
		if(GTK_TOGGLE_BUTTON(widget)->active)
		{
			if((char *)data=="student") /*学生登录*/
			{
				identity = 1;
			}
			else if((char *)data=="teacher")  /*教师登录*/
			{
				identity = 2;
			}
			else   /*管理员登录*/
			{
				identity = 3;
			}
		}
}


int main(int argc, char*argv[])
{
		GladeXML *LoginXML;
		GtkWidget *login_button, *exit_button;
		GtkWidget *student_radio,*teacher_radio,*admin_radio;   /*单选按钮*/					
		gtk_init(&argc,&argv);
		LoginXML = glade_xml_new("ui/login.glade", NULL, NULL);
		login_window = glade_xml_get_widget(LoginXML, "window");
		glade_xml_signal_autoconnect(LoginXML);
		name_entry = glade_xml_get_widget(LoginXML, "name_entry");
		pwd_entry = glade_xml_get_widget(LoginXML, "pwd_entry");
		student_radio = glade_xml_get_widget(LoginXML, "student");
		g_signal_connect(GTK_OBJECT(student_radio),"clicked",G_CALLBACK(radiobutton_clicked),"student");
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(student_radio),TRUE);
		/*学生按钮设置为默认选中状态*/
		teacher_radio = glade_xml_get_widget(LoginXML, "teacher");
		g_signal_connect(GTK_OBJECT(teacher_radio),"clicked",G_CALLBACK(radiobutton_clicked),"teacher");
		admin_radio = glade_xml_get_widget(LoginXML, "admin");
		g_signal_connect(GTK_OBJECT(admin_radio),"clicked",G_CALLBACK(radiobutton_clicked),"admin");
		login_button = glade_xml_get_widget(LoginXML, "login_button");
		g_signal_connect(G_OBJECT(login_button), "clicked",G_CALLBACK(on_login_button_clicked), login_window);
		exit_button = glade_xml_get_widget(LoginXML, "exit_button");
		g_signal_connect(G_OBJECT(exit_button), "clicked",G_CALLBACK(gtk_main_quit), login_window);
		g_signal_connect(G_OBJECT(login_window),"destroy",G_CALLBACK(gtk_main_quit),login_window);
		gtk_widget_show_all(login_window);
		gtk_main();
		return 0;
}

	
		GladeXML *LoginXML;
		GtkWidget *login_button, *exit_button;
		GtkWidget *student_radio,*teacher_radio,*admin_radio;   /*单选按钮*/
				
		gtk_init(&argc,&argv);	
		LoginXML = glade_xml_new("ui/login.glade", NULL, NULL);
		login_window = glade_xml_get_widget(LoginXML, "window");
		glade_xml_signal_autoconnect(LoginXML);
		
		name_entry = glade_xml_get_widget(LoginXML, "name_entry");
		pwd_entry = glade_xml_get_widget(LoginXML, "pwd_entry");
		
		student_radio = glade_xml_get_widget(LoginXML, "student");
		g_signal_connect(GTK_OBJECT(student_radio),"clicked",G_CALLBACK(radiobutton_clicked),"student");
		//gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(student_radio),TRUE);/*学生按钮设置为默认选中状态*/
		teacher_radio = glade_xml_get_widget(LoginXML, "teacher");
		g_signal_connect(GTK_OBJECT(teacher_radio),"clicked",G_CALLBACK(radiobutton_clicked),"teacher");
		admin_radio = glade_xml_get_widget(LoginXML, "admin");
		g_signal_connect(GTK_OBJECT(admin_radio),"clicked",G_CALLBACK(radiobutton_clicked),"admin");
		
		login_button = glade_xml_get_widget(LoginXML, "login_button");
		g_signal_connect(G_OBJECT(login_button), "clicked", G_CALLBACK(on_login_button_clicked), login_window);
		
		exit_button = glade_xml_get_widget(LoginXML, "exit_button");
		g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(gtk_main_quit), login_window);
		g_signal_connect(G_OBJECT(login_window),"destroy",G_CALLBACK(gtk_main_quit),login_window);
		gtk_widget_show_all(login_window);
		gtk_main();	
		return 0;
}
