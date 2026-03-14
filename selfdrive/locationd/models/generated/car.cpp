#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5099663246558865105) {
   out_5099663246558865105[0] = delta_x[0] + nom_x[0];
   out_5099663246558865105[1] = delta_x[1] + nom_x[1];
   out_5099663246558865105[2] = delta_x[2] + nom_x[2];
   out_5099663246558865105[3] = delta_x[3] + nom_x[3];
   out_5099663246558865105[4] = delta_x[4] + nom_x[4];
   out_5099663246558865105[5] = delta_x[5] + nom_x[5];
   out_5099663246558865105[6] = delta_x[6] + nom_x[6];
   out_5099663246558865105[7] = delta_x[7] + nom_x[7];
   out_5099663246558865105[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6295017046594980417) {
   out_6295017046594980417[0] = -nom_x[0] + true_x[0];
   out_6295017046594980417[1] = -nom_x[1] + true_x[1];
   out_6295017046594980417[2] = -nom_x[2] + true_x[2];
   out_6295017046594980417[3] = -nom_x[3] + true_x[3];
   out_6295017046594980417[4] = -nom_x[4] + true_x[4];
   out_6295017046594980417[5] = -nom_x[5] + true_x[5];
   out_6295017046594980417[6] = -nom_x[6] + true_x[6];
   out_6295017046594980417[7] = -nom_x[7] + true_x[7];
   out_6295017046594980417[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1959530448758324830) {
   out_1959530448758324830[0] = 1.0;
   out_1959530448758324830[1] = 0.0;
   out_1959530448758324830[2] = 0.0;
   out_1959530448758324830[3] = 0.0;
   out_1959530448758324830[4] = 0.0;
   out_1959530448758324830[5] = 0.0;
   out_1959530448758324830[6] = 0.0;
   out_1959530448758324830[7] = 0.0;
   out_1959530448758324830[8] = 0.0;
   out_1959530448758324830[9] = 0.0;
   out_1959530448758324830[10] = 1.0;
   out_1959530448758324830[11] = 0.0;
   out_1959530448758324830[12] = 0.0;
   out_1959530448758324830[13] = 0.0;
   out_1959530448758324830[14] = 0.0;
   out_1959530448758324830[15] = 0.0;
   out_1959530448758324830[16] = 0.0;
   out_1959530448758324830[17] = 0.0;
   out_1959530448758324830[18] = 0.0;
   out_1959530448758324830[19] = 0.0;
   out_1959530448758324830[20] = 1.0;
   out_1959530448758324830[21] = 0.0;
   out_1959530448758324830[22] = 0.0;
   out_1959530448758324830[23] = 0.0;
   out_1959530448758324830[24] = 0.0;
   out_1959530448758324830[25] = 0.0;
   out_1959530448758324830[26] = 0.0;
   out_1959530448758324830[27] = 0.0;
   out_1959530448758324830[28] = 0.0;
   out_1959530448758324830[29] = 0.0;
   out_1959530448758324830[30] = 1.0;
   out_1959530448758324830[31] = 0.0;
   out_1959530448758324830[32] = 0.0;
   out_1959530448758324830[33] = 0.0;
   out_1959530448758324830[34] = 0.0;
   out_1959530448758324830[35] = 0.0;
   out_1959530448758324830[36] = 0.0;
   out_1959530448758324830[37] = 0.0;
   out_1959530448758324830[38] = 0.0;
   out_1959530448758324830[39] = 0.0;
   out_1959530448758324830[40] = 1.0;
   out_1959530448758324830[41] = 0.0;
   out_1959530448758324830[42] = 0.0;
   out_1959530448758324830[43] = 0.0;
   out_1959530448758324830[44] = 0.0;
   out_1959530448758324830[45] = 0.0;
   out_1959530448758324830[46] = 0.0;
   out_1959530448758324830[47] = 0.0;
   out_1959530448758324830[48] = 0.0;
   out_1959530448758324830[49] = 0.0;
   out_1959530448758324830[50] = 1.0;
   out_1959530448758324830[51] = 0.0;
   out_1959530448758324830[52] = 0.0;
   out_1959530448758324830[53] = 0.0;
   out_1959530448758324830[54] = 0.0;
   out_1959530448758324830[55] = 0.0;
   out_1959530448758324830[56] = 0.0;
   out_1959530448758324830[57] = 0.0;
   out_1959530448758324830[58] = 0.0;
   out_1959530448758324830[59] = 0.0;
   out_1959530448758324830[60] = 1.0;
   out_1959530448758324830[61] = 0.0;
   out_1959530448758324830[62] = 0.0;
   out_1959530448758324830[63] = 0.0;
   out_1959530448758324830[64] = 0.0;
   out_1959530448758324830[65] = 0.0;
   out_1959530448758324830[66] = 0.0;
   out_1959530448758324830[67] = 0.0;
   out_1959530448758324830[68] = 0.0;
   out_1959530448758324830[69] = 0.0;
   out_1959530448758324830[70] = 1.0;
   out_1959530448758324830[71] = 0.0;
   out_1959530448758324830[72] = 0.0;
   out_1959530448758324830[73] = 0.0;
   out_1959530448758324830[74] = 0.0;
   out_1959530448758324830[75] = 0.0;
   out_1959530448758324830[76] = 0.0;
   out_1959530448758324830[77] = 0.0;
   out_1959530448758324830[78] = 0.0;
   out_1959530448758324830[79] = 0.0;
   out_1959530448758324830[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_12403835329328763) {
   out_12403835329328763[0] = state[0];
   out_12403835329328763[1] = state[1];
   out_12403835329328763[2] = state[2];
   out_12403835329328763[3] = state[3];
   out_12403835329328763[4] = state[4];
   out_12403835329328763[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_12403835329328763[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_12403835329328763[7] = state[7];
   out_12403835329328763[8] = state[8];
}
void F_fun(double *state, double dt, double *out_336602172735076655) {
   out_336602172735076655[0] = 1;
   out_336602172735076655[1] = 0;
   out_336602172735076655[2] = 0;
   out_336602172735076655[3] = 0;
   out_336602172735076655[4] = 0;
   out_336602172735076655[5] = 0;
   out_336602172735076655[6] = 0;
   out_336602172735076655[7] = 0;
   out_336602172735076655[8] = 0;
   out_336602172735076655[9] = 0;
   out_336602172735076655[10] = 1;
   out_336602172735076655[11] = 0;
   out_336602172735076655[12] = 0;
   out_336602172735076655[13] = 0;
   out_336602172735076655[14] = 0;
   out_336602172735076655[15] = 0;
   out_336602172735076655[16] = 0;
   out_336602172735076655[17] = 0;
   out_336602172735076655[18] = 0;
   out_336602172735076655[19] = 0;
   out_336602172735076655[20] = 1;
   out_336602172735076655[21] = 0;
   out_336602172735076655[22] = 0;
   out_336602172735076655[23] = 0;
   out_336602172735076655[24] = 0;
   out_336602172735076655[25] = 0;
   out_336602172735076655[26] = 0;
   out_336602172735076655[27] = 0;
   out_336602172735076655[28] = 0;
   out_336602172735076655[29] = 0;
   out_336602172735076655[30] = 1;
   out_336602172735076655[31] = 0;
   out_336602172735076655[32] = 0;
   out_336602172735076655[33] = 0;
   out_336602172735076655[34] = 0;
   out_336602172735076655[35] = 0;
   out_336602172735076655[36] = 0;
   out_336602172735076655[37] = 0;
   out_336602172735076655[38] = 0;
   out_336602172735076655[39] = 0;
   out_336602172735076655[40] = 1;
   out_336602172735076655[41] = 0;
   out_336602172735076655[42] = 0;
   out_336602172735076655[43] = 0;
   out_336602172735076655[44] = 0;
   out_336602172735076655[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_336602172735076655[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_336602172735076655[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_336602172735076655[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_336602172735076655[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_336602172735076655[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_336602172735076655[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_336602172735076655[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_336602172735076655[53] = -9.8100000000000005*dt;
   out_336602172735076655[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_336602172735076655[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_336602172735076655[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_336602172735076655[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_336602172735076655[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_336602172735076655[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_336602172735076655[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_336602172735076655[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_336602172735076655[62] = 0;
   out_336602172735076655[63] = 0;
   out_336602172735076655[64] = 0;
   out_336602172735076655[65] = 0;
   out_336602172735076655[66] = 0;
   out_336602172735076655[67] = 0;
   out_336602172735076655[68] = 0;
   out_336602172735076655[69] = 0;
   out_336602172735076655[70] = 1;
   out_336602172735076655[71] = 0;
   out_336602172735076655[72] = 0;
   out_336602172735076655[73] = 0;
   out_336602172735076655[74] = 0;
   out_336602172735076655[75] = 0;
   out_336602172735076655[76] = 0;
   out_336602172735076655[77] = 0;
   out_336602172735076655[78] = 0;
   out_336602172735076655[79] = 0;
   out_336602172735076655[80] = 1;
}
void h_25(double *state, double *unused, double *out_5547362161313289216) {
   out_5547362161313289216[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5482511098747816507) {
   out_5482511098747816507[0] = 0;
   out_5482511098747816507[1] = 0;
   out_5482511098747816507[2] = 0;
   out_5482511098747816507[3] = 0;
   out_5482511098747816507[4] = 0;
   out_5482511098747816507[5] = 0;
   out_5482511098747816507[6] = 1;
   out_5482511098747816507[7] = 0;
   out_5482511098747816507[8] = 0;
}
void h_24(double *state, double *unused, double *out_978331752955715563) {
   out_978331752955715563[0] = state[4];
   out_978331752955715563[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6310027516853549352) {
   out_6310027516853549352[0] = 0;
   out_6310027516853549352[1] = 0;
   out_6310027516853549352[2] = 0;
   out_6310027516853549352[3] = 0;
   out_6310027516853549352[4] = 1;
   out_6310027516853549352[5] = 0;
   out_6310027516853549352[6] = 0;
   out_6310027516853549352[7] = 0;
   out_6310027516853549352[8] = 0;
   out_6310027516853549352[9] = 0;
   out_6310027516853549352[10] = 0;
   out_6310027516853549352[11] = 0;
   out_6310027516853549352[12] = 0;
   out_6310027516853549352[13] = 0;
   out_6310027516853549352[14] = 1;
   out_6310027516853549352[15] = 0;
   out_6310027516853549352[16] = 0;
   out_6310027516853549352[17] = 0;
}
void h_30(double *state, double *unused, double *out_4259504435677720516) {
   out_4259504435677720516[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5353172151604576437) {
   out_5353172151604576437[0] = 0;
   out_5353172151604576437[1] = 0;
   out_5353172151604576437[2] = 0;
   out_5353172151604576437[3] = 0;
   out_5353172151604576437[4] = 1;
   out_5353172151604576437[5] = 0;
   out_5353172151604576437[6] = 0;
   out_5353172151604576437[7] = 0;
   out_5353172151604576437[8] = 0;
}
void h_26(double *state, double *unused, double *out_7072056538947573899) {
   out_7072056538947573899[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6139365162858128411) {
   out_6139365162858128411[0] = 0;
   out_6139365162858128411[1] = 0;
   out_6139365162858128411[2] = 0;
   out_6139365162858128411[3] = 0;
   out_6139365162858128411[4] = 0;
   out_6139365162858128411[5] = 0;
   out_6139365162858128411[6] = 0;
   out_6139365162858128411[7] = 1;
   out_6139365162858128411[8] = 0;
}
void h_27(double *state, double *unused, double *out_4944046276636811699) {
   out_4944046276636811699[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3178408839804151526) {
   out_3178408839804151526[0] = 0;
   out_3178408839804151526[1] = 0;
   out_3178408839804151526[2] = 0;
   out_3178408839804151526[3] = 1;
   out_3178408839804151526[4] = 0;
   out_3178408839804151526[5] = 0;
   out_3178408839804151526[6] = 0;
   out_3178408839804151526[7] = 0;
   out_3178408839804151526[8] = 0;
}
void h_29(double *state, double *unused, double *out_1306596748382789349) {
   out_1306596748382789349[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5863403495918968621) {
   out_5863403495918968621[0] = 0;
   out_5863403495918968621[1] = 1;
   out_5863403495918968621[2] = 0;
   out_5863403495918968621[3] = 0;
   out_5863403495918968621[4] = 0;
   out_5863403495918968621[5] = 0;
   out_5863403495918968621[6] = 0;
   out_5863403495918968621[7] = 0;
   out_5863403495918968621[8] = 0;
}
void h_28(double *state, double *unused, double *out_3961962183301513587) {
   out_3961962183301513587[0] = state[0];
}
void H_28(double *state, double *unused, double *out_781004478849438047) {
   out_781004478849438047[0] = 1;
   out_781004478849438047[1] = 0;
   out_781004478849438047[2] = 0;
   out_781004478849438047[3] = 0;
   out_781004478849438047[4] = 0;
   out_781004478849438047[5] = 0;
   out_781004478849438047[6] = 0;
   out_781004478849438047[7] = 0;
   out_781004478849438047[8] = 0;
}
void h_31(double *state, double *unused, double *out_5822556223597795105) {
   out_5822556223597795105[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5513157060624776935) {
   out_5513157060624776935[0] = 0;
   out_5513157060624776935[1] = 0;
   out_5513157060624776935[2] = 0;
   out_5513157060624776935[3] = 0;
   out_5513157060624776935[4] = 0;
   out_5513157060624776935[5] = 0;
   out_5513157060624776935[6] = 0;
   out_5513157060624776935[7] = 0;
   out_5513157060624776935[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_5099663246558865105) {
  err_fun(nom_x, delta_x, out_5099663246558865105);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6295017046594980417) {
  inv_err_fun(nom_x, true_x, out_6295017046594980417);
}
void car_H_mod_fun(double *state, double *out_1959530448758324830) {
  H_mod_fun(state, out_1959530448758324830);
}
void car_f_fun(double *state, double dt, double *out_12403835329328763) {
  f_fun(state,  dt, out_12403835329328763);
}
void car_F_fun(double *state, double dt, double *out_336602172735076655) {
  F_fun(state,  dt, out_336602172735076655);
}
void car_h_25(double *state, double *unused, double *out_5547362161313289216) {
  h_25(state, unused, out_5547362161313289216);
}
void car_H_25(double *state, double *unused, double *out_5482511098747816507) {
  H_25(state, unused, out_5482511098747816507);
}
void car_h_24(double *state, double *unused, double *out_978331752955715563) {
  h_24(state, unused, out_978331752955715563);
}
void car_H_24(double *state, double *unused, double *out_6310027516853549352) {
  H_24(state, unused, out_6310027516853549352);
}
void car_h_30(double *state, double *unused, double *out_4259504435677720516) {
  h_30(state, unused, out_4259504435677720516);
}
void car_H_30(double *state, double *unused, double *out_5353172151604576437) {
  H_30(state, unused, out_5353172151604576437);
}
void car_h_26(double *state, double *unused, double *out_7072056538947573899) {
  h_26(state, unused, out_7072056538947573899);
}
void car_H_26(double *state, double *unused, double *out_6139365162858128411) {
  H_26(state, unused, out_6139365162858128411);
}
void car_h_27(double *state, double *unused, double *out_4944046276636811699) {
  h_27(state, unused, out_4944046276636811699);
}
void car_H_27(double *state, double *unused, double *out_3178408839804151526) {
  H_27(state, unused, out_3178408839804151526);
}
void car_h_29(double *state, double *unused, double *out_1306596748382789349) {
  h_29(state, unused, out_1306596748382789349);
}
void car_H_29(double *state, double *unused, double *out_5863403495918968621) {
  H_29(state, unused, out_5863403495918968621);
}
void car_h_28(double *state, double *unused, double *out_3961962183301513587) {
  h_28(state, unused, out_3961962183301513587);
}
void car_H_28(double *state, double *unused, double *out_781004478849438047) {
  H_28(state, unused, out_781004478849438047);
}
void car_h_31(double *state, double *unused, double *out_5822556223597795105) {
  h_31(state, unused, out_5822556223597795105);
}
void car_H_31(double *state, double *unused, double *out_5513157060624776935) {
  H_31(state, unused, out_5513157060624776935);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
