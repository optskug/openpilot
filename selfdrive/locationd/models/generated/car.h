#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5099663246558865105);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6295017046594980417);
void car_H_mod_fun(double *state, double *out_1959530448758324830);
void car_f_fun(double *state, double dt, double *out_12403835329328763);
void car_F_fun(double *state, double dt, double *out_336602172735076655);
void car_h_25(double *state, double *unused, double *out_5547362161313289216);
void car_H_25(double *state, double *unused, double *out_5482511098747816507);
void car_h_24(double *state, double *unused, double *out_978331752955715563);
void car_H_24(double *state, double *unused, double *out_6310027516853549352);
void car_h_30(double *state, double *unused, double *out_4259504435677720516);
void car_H_30(double *state, double *unused, double *out_5353172151604576437);
void car_h_26(double *state, double *unused, double *out_7072056538947573899);
void car_H_26(double *state, double *unused, double *out_6139365162858128411);
void car_h_27(double *state, double *unused, double *out_4944046276636811699);
void car_H_27(double *state, double *unused, double *out_3178408839804151526);
void car_h_29(double *state, double *unused, double *out_1306596748382789349);
void car_H_29(double *state, double *unused, double *out_5863403495918968621);
void car_h_28(double *state, double *unused, double *out_3961962183301513587);
void car_H_28(double *state, double *unused, double *out_781004478849438047);
void car_h_31(double *state, double *unused, double *out_5822556223597795105);
void car_H_31(double *state, double *unused, double *out_5513157060624776935);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}