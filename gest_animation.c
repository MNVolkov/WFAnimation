/*
	(С) Волков Максим 2019 ( mr-volkov+bip@yandex.ru )
	
	Анимация циферблата при жесте взмахивания для просмотра времени
	При определении жеста, на экране часов будет показана анимация из ресурсов

*/

#include <libbip.h>
#include "gest_animation.h"

struct regmenu_ menu_gest_animation = {
						55,
						1,
						0,
						dispatch_animation,			//	dispatch
						key_press_screen,			//	key_press 
						gest_animation_screen_job,	//	screen_job,
						0,
						show_gesture_animation,
						0,
						0
					};
					
int main(int param0, char** argv){	//	переменная argv не определена
	show_gesture_animation((void*) param0);
	return 0;
}

void show_gesture_animation(void* param0){
struct gest_ani_struct** 	anidata_p = get_ptr_temp_buf_1(); 	//	указатель на указатель на номер кадра
struct gest_ani_struct *	anidata;							//	указатель на номер кадра

reg_menu(&menu_gest_animation, 1); // регистрируем оверлейный экран

*anidata_p = (struct gest_ani_struct*)pvPortMalloc(sizeof(struct gest_ani_struct));
anidata = *anidata_p;		//	указатель на данные
_memclr(anidata, sizeof(struct gest_ani_struct));

anidata->proc = param0;

// запомним адрес указателя на функцию в которую необходимо вернуться после завершения данного экрана
if ( param0 ) 			//	если указатель на возврат передан, то возвоащаемся на него
	anidata->ret_f = anidata->proc->elf_finish;
else					//	если нет, то на циферблат
	anidata->ret_f = show_watchface;


// первый кадр нулевой
anidata->frame = 0;

set_bg_color(COLOR_BLACK);
fill_screen_bg();

set_graph_callback_to_ram_1();
load_font();

set_update_period(1, ANIMATION_FRAME_TIME);

}

void key_press_screen(){
struct gest_ani_struct** 	anidata_p = get_ptr_temp_buf_1();	//	указатель на указатель на номер кадра
struct gest_ani_struct *	anidata = *anidata_p;					//	указатель на номер кадра

// вызываем функцию возврата (обычно это меню запуска), в качестве параметра указываем адрес функции нашего приложения
show_menu(anidata->ret_f, (int) show_gesture_animation);	
};


int dispatch_animation(void *param){
struct gest_ani_struct** 	anidata_p = get_ptr_temp_buf_1();	//	указатель на указатель на номер кадра
struct gest_ani_struct *	anidata = *anidata_p;					//	указатель на номер кадра

// вызываем функцию возврата (обычно это меню запуска), в качестве параметра указываем адрес функции нашего приложения
show_menu(anidata->ret_f, (int) show_gesture_animation);	
return 0;
}

int gest_animation_screen_job(){

struct gest_ani_struct** 	anidata_p = get_ptr_temp_buf_1();	//	указатель на указатель на номер кадра
struct gest_ani_struct *	anidata = *anidata_p;					//	указатель на номер кадра

show_elf_res_by_id(anidata->proc->index_listed, anidata->frame+ANIMATION_FIRST_FRAME, 0, 0 );
repaint_screen_lines(0, 176);

 if ( anidata->frame < ANIMATION_FRAME_COUNT ) {
    set_update_period(1, ANIMATION_FRAME_TIME);
	anidata->frame++;
 }
  else
 {  
	//void**	param_p =  temp_buf_2;
	//void* 	param 	= *param_p;
	
	show_menu(anidata->ret_f, (int) show_gesture_animation);
 }
 
 return 0;
}