#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6893490668885513914);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4691374393904796900);
void pose_H_mod_fun(double *state, double *out_4137219385418974808);
void pose_f_fun(double *state, double dt, double *out_1005410473172106637);
void pose_F_fun(double *state, double dt, double *out_5217597012244076167);
void pose_h_4(double *state, double *unused, double *out_1497349936567297536);
void pose_H_4(double *state, double *unused, double *out_1129598351143808372);
void pose_h_10(double *state, double *unused, double *out_3534162960479099254);
void pose_H_10(double *state, double *unused, double *out_240511820445146055);
void pose_h_13(double *state, double *unused, double *out_2296308651892447689);
void pose_H_13(double *state, double *unused, double *out_6481032857172892557);
void pose_h_14(double *state, double *unused, double *out_5180046062651358956);
void pose_H_14(double *state, double *unused, double *out_2833642505195676157);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}