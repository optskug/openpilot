#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7224170274929451769);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_580510085257942810);
void pose_H_mod_fun(double *state, double *out_7521149564861609621);
void pose_f_fun(double *state, double dt, double *out_5784399927549256008);
void pose_F_fun(double *state, double dt, double *out_7477745333434750070);
void pose_h_4(double *state, double *unused, double *out_3625361759125608085);
void pose_H_4(double *state, double *unused, double *out_1981232842790120653);
void pose_h_10(double *state, double *unused, double *out_1179392119798824446);
void pose_H_10(double *state, double *unused, double *out_1288900125489167846);
void pose_h_13(double *state, double *unused, double *out_5336829018404406652);
void pose_H_13(double *state, double *unused, double *out_5193506668122453454);
void pose_h_14(double *state, double *unused, double *out_2890500241112110034);
void pose_H_14(double *state, double *unused, double *out_5944473699129605182);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}