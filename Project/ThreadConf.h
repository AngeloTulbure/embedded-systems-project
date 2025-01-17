#ifndef THREADCONF_H
#define THREADCONF_H
void thread_start();
void thread_pause();
void thread_principal();
void thread_player();
void thread_sound();
void show_sequence();
int calculate_timeout(int pot_value, int num_intervals);
int calculate_speed_delay(int pot_value, int num_intervals);
#endif
