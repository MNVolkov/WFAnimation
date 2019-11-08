/*
	(С) Волков Максим 2019 ( mr-volkov+bip@yandex.ru )
	
	Анимация циферблата при жесте взмахивания для просмотра времени
	При определении жеста, на экране часов будет показана анимация из ресурсов

*/

#ifndef __GEST_ANIM_H__
#define __GEST_ANIM_H__

// структура данных содержащая информацию 10 будильников
struct gest_ani_struct {
	int 	frame;		//номер отображаемого кадра
	Elf_proc_* proc;	//	указатель на данные запущенного процесса
	void* 	ret_f;		//	адрес функции возврата
};

// выбранный разряд изменения минут
#define ANIMATION_FIRST_FRAME	0 	//	номер ресурса первого кадра
#define ANIMATION_FRAME_TIME	5	//	время обновления кадров
#define ANIMATION_FRAME_COUNT	11	//	количество кадров после которых выход

// gest_animation.c
int 	gest_animation_screen_job();
void 	show_gesture_animation(void* param);
int		dispatch_animation(void *param);
void 	key_press_screen();

#endif