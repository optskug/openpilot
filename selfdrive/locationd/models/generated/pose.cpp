#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_6893490668885513914) {
   out_6893490668885513914[0] = delta_x[0] + nom_x[0];
   out_6893490668885513914[1] = delta_x[1] + nom_x[1];
   out_6893490668885513914[2] = delta_x[2] + nom_x[2];
   out_6893490668885513914[3] = delta_x[3] + nom_x[3];
   out_6893490668885513914[4] = delta_x[4] + nom_x[4];
   out_6893490668885513914[5] = delta_x[5] + nom_x[5];
   out_6893490668885513914[6] = delta_x[6] + nom_x[6];
   out_6893490668885513914[7] = delta_x[7] + nom_x[7];
   out_6893490668885513914[8] = delta_x[8] + nom_x[8];
   out_6893490668885513914[9] = delta_x[9] + nom_x[9];
   out_6893490668885513914[10] = delta_x[10] + nom_x[10];
   out_6893490668885513914[11] = delta_x[11] + nom_x[11];
   out_6893490668885513914[12] = delta_x[12] + nom_x[12];
   out_6893490668885513914[13] = delta_x[13] + nom_x[13];
   out_6893490668885513914[14] = delta_x[14] + nom_x[14];
   out_6893490668885513914[15] = delta_x[15] + nom_x[15];
   out_6893490668885513914[16] = delta_x[16] + nom_x[16];
   out_6893490668885513914[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4691374393904796900) {
   out_4691374393904796900[0] = -nom_x[0] + true_x[0];
   out_4691374393904796900[1] = -nom_x[1] + true_x[1];
   out_4691374393904796900[2] = -nom_x[2] + true_x[2];
   out_4691374393904796900[3] = -nom_x[3] + true_x[3];
   out_4691374393904796900[4] = -nom_x[4] + true_x[4];
   out_4691374393904796900[5] = -nom_x[5] + true_x[5];
   out_4691374393904796900[6] = -nom_x[6] + true_x[6];
   out_4691374393904796900[7] = -nom_x[7] + true_x[7];
   out_4691374393904796900[8] = -nom_x[8] + true_x[8];
   out_4691374393904796900[9] = -nom_x[9] + true_x[9];
   out_4691374393904796900[10] = -nom_x[10] + true_x[10];
   out_4691374393904796900[11] = -nom_x[11] + true_x[11];
   out_4691374393904796900[12] = -nom_x[12] + true_x[12];
   out_4691374393904796900[13] = -nom_x[13] + true_x[13];
   out_4691374393904796900[14] = -nom_x[14] + true_x[14];
   out_4691374393904796900[15] = -nom_x[15] + true_x[15];
   out_4691374393904796900[16] = -nom_x[16] + true_x[16];
   out_4691374393904796900[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4137219385418974808) {
   out_4137219385418974808[0] = 1.0;
   out_4137219385418974808[1] = 0.0;
   out_4137219385418974808[2] = 0.0;
   out_4137219385418974808[3] = 0.0;
   out_4137219385418974808[4] = 0.0;
   out_4137219385418974808[5] = 0.0;
   out_4137219385418974808[6] = 0.0;
   out_4137219385418974808[7] = 0.0;
   out_4137219385418974808[8] = 0.0;
   out_4137219385418974808[9] = 0.0;
   out_4137219385418974808[10] = 0.0;
   out_4137219385418974808[11] = 0.0;
   out_4137219385418974808[12] = 0.0;
   out_4137219385418974808[13] = 0.0;
   out_4137219385418974808[14] = 0.0;
   out_4137219385418974808[15] = 0.0;
   out_4137219385418974808[16] = 0.0;
   out_4137219385418974808[17] = 0.0;
   out_4137219385418974808[18] = 0.0;
   out_4137219385418974808[19] = 1.0;
   out_4137219385418974808[20] = 0.0;
   out_4137219385418974808[21] = 0.0;
   out_4137219385418974808[22] = 0.0;
   out_4137219385418974808[23] = 0.0;
   out_4137219385418974808[24] = 0.0;
   out_4137219385418974808[25] = 0.0;
   out_4137219385418974808[26] = 0.0;
   out_4137219385418974808[27] = 0.0;
   out_4137219385418974808[28] = 0.0;
   out_4137219385418974808[29] = 0.0;
   out_4137219385418974808[30] = 0.0;
   out_4137219385418974808[31] = 0.0;
   out_4137219385418974808[32] = 0.0;
   out_4137219385418974808[33] = 0.0;
   out_4137219385418974808[34] = 0.0;
   out_4137219385418974808[35] = 0.0;
   out_4137219385418974808[36] = 0.0;
   out_4137219385418974808[37] = 0.0;
   out_4137219385418974808[38] = 1.0;
   out_4137219385418974808[39] = 0.0;
   out_4137219385418974808[40] = 0.0;
   out_4137219385418974808[41] = 0.0;
   out_4137219385418974808[42] = 0.0;
   out_4137219385418974808[43] = 0.0;
   out_4137219385418974808[44] = 0.0;
   out_4137219385418974808[45] = 0.0;
   out_4137219385418974808[46] = 0.0;
   out_4137219385418974808[47] = 0.0;
   out_4137219385418974808[48] = 0.0;
   out_4137219385418974808[49] = 0.0;
   out_4137219385418974808[50] = 0.0;
   out_4137219385418974808[51] = 0.0;
   out_4137219385418974808[52] = 0.0;
   out_4137219385418974808[53] = 0.0;
   out_4137219385418974808[54] = 0.0;
   out_4137219385418974808[55] = 0.0;
   out_4137219385418974808[56] = 0.0;
   out_4137219385418974808[57] = 1.0;
   out_4137219385418974808[58] = 0.0;
   out_4137219385418974808[59] = 0.0;
   out_4137219385418974808[60] = 0.0;
   out_4137219385418974808[61] = 0.0;
   out_4137219385418974808[62] = 0.0;
   out_4137219385418974808[63] = 0.0;
   out_4137219385418974808[64] = 0.0;
   out_4137219385418974808[65] = 0.0;
   out_4137219385418974808[66] = 0.0;
   out_4137219385418974808[67] = 0.0;
   out_4137219385418974808[68] = 0.0;
   out_4137219385418974808[69] = 0.0;
   out_4137219385418974808[70] = 0.0;
   out_4137219385418974808[71] = 0.0;
   out_4137219385418974808[72] = 0.0;
   out_4137219385418974808[73] = 0.0;
   out_4137219385418974808[74] = 0.0;
   out_4137219385418974808[75] = 0.0;
   out_4137219385418974808[76] = 1.0;
   out_4137219385418974808[77] = 0.0;
   out_4137219385418974808[78] = 0.0;
   out_4137219385418974808[79] = 0.0;
   out_4137219385418974808[80] = 0.0;
   out_4137219385418974808[81] = 0.0;
   out_4137219385418974808[82] = 0.0;
   out_4137219385418974808[83] = 0.0;
   out_4137219385418974808[84] = 0.0;
   out_4137219385418974808[85] = 0.0;
   out_4137219385418974808[86] = 0.0;
   out_4137219385418974808[87] = 0.0;
   out_4137219385418974808[88] = 0.0;
   out_4137219385418974808[89] = 0.0;
   out_4137219385418974808[90] = 0.0;
   out_4137219385418974808[91] = 0.0;
   out_4137219385418974808[92] = 0.0;
   out_4137219385418974808[93] = 0.0;
   out_4137219385418974808[94] = 0.0;
   out_4137219385418974808[95] = 1.0;
   out_4137219385418974808[96] = 0.0;
   out_4137219385418974808[97] = 0.0;
   out_4137219385418974808[98] = 0.0;
   out_4137219385418974808[99] = 0.0;
   out_4137219385418974808[100] = 0.0;
   out_4137219385418974808[101] = 0.0;
   out_4137219385418974808[102] = 0.0;
   out_4137219385418974808[103] = 0.0;
   out_4137219385418974808[104] = 0.0;
   out_4137219385418974808[105] = 0.0;
   out_4137219385418974808[106] = 0.0;
   out_4137219385418974808[107] = 0.0;
   out_4137219385418974808[108] = 0.0;
   out_4137219385418974808[109] = 0.0;
   out_4137219385418974808[110] = 0.0;
   out_4137219385418974808[111] = 0.0;
   out_4137219385418974808[112] = 0.0;
   out_4137219385418974808[113] = 0.0;
   out_4137219385418974808[114] = 1.0;
   out_4137219385418974808[115] = 0.0;
   out_4137219385418974808[116] = 0.0;
   out_4137219385418974808[117] = 0.0;
   out_4137219385418974808[118] = 0.0;
   out_4137219385418974808[119] = 0.0;
   out_4137219385418974808[120] = 0.0;
   out_4137219385418974808[121] = 0.0;
   out_4137219385418974808[122] = 0.0;
   out_4137219385418974808[123] = 0.0;
   out_4137219385418974808[124] = 0.0;
   out_4137219385418974808[125] = 0.0;
   out_4137219385418974808[126] = 0.0;
   out_4137219385418974808[127] = 0.0;
   out_4137219385418974808[128] = 0.0;
   out_4137219385418974808[129] = 0.0;
   out_4137219385418974808[130] = 0.0;
   out_4137219385418974808[131] = 0.0;
   out_4137219385418974808[132] = 0.0;
   out_4137219385418974808[133] = 1.0;
   out_4137219385418974808[134] = 0.0;
   out_4137219385418974808[135] = 0.0;
   out_4137219385418974808[136] = 0.0;
   out_4137219385418974808[137] = 0.0;
   out_4137219385418974808[138] = 0.0;
   out_4137219385418974808[139] = 0.0;
   out_4137219385418974808[140] = 0.0;
   out_4137219385418974808[141] = 0.0;
   out_4137219385418974808[142] = 0.0;
   out_4137219385418974808[143] = 0.0;
   out_4137219385418974808[144] = 0.0;
   out_4137219385418974808[145] = 0.0;
   out_4137219385418974808[146] = 0.0;
   out_4137219385418974808[147] = 0.0;
   out_4137219385418974808[148] = 0.0;
   out_4137219385418974808[149] = 0.0;
   out_4137219385418974808[150] = 0.0;
   out_4137219385418974808[151] = 0.0;
   out_4137219385418974808[152] = 1.0;
   out_4137219385418974808[153] = 0.0;
   out_4137219385418974808[154] = 0.0;
   out_4137219385418974808[155] = 0.0;
   out_4137219385418974808[156] = 0.0;
   out_4137219385418974808[157] = 0.0;
   out_4137219385418974808[158] = 0.0;
   out_4137219385418974808[159] = 0.0;
   out_4137219385418974808[160] = 0.0;
   out_4137219385418974808[161] = 0.0;
   out_4137219385418974808[162] = 0.0;
   out_4137219385418974808[163] = 0.0;
   out_4137219385418974808[164] = 0.0;
   out_4137219385418974808[165] = 0.0;
   out_4137219385418974808[166] = 0.0;
   out_4137219385418974808[167] = 0.0;
   out_4137219385418974808[168] = 0.0;
   out_4137219385418974808[169] = 0.0;
   out_4137219385418974808[170] = 0.0;
   out_4137219385418974808[171] = 1.0;
   out_4137219385418974808[172] = 0.0;
   out_4137219385418974808[173] = 0.0;
   out_4137219385418974808[174] = 0.0;
   out_4137219385418974808[175] = 0.0;
   out_4137219385418974808[176] = 0.0;
   out_4137219385418974808[177] = 0.0;
   out_4137219385418974808[178] = 0.0;
   out_4137219385418974808[179] = 0.0;
   out_4137219385418974808[180] = 0.0;
   out_4137219385418974808[181] = 0.0;
   out_4137219385418974808[182] = 0.0;
   out_4137219385418974808[183] = 0.0;
   out_4137219385418974808[184] = 0.0;
   out_4137219385418974808[185] = 0.0;
   out_4137219385418974808[186] = 0.0;
   out_4137219385418974808[187] = 0.0;
   out_4137219385418974808[188] = 0.0;
   out_4137219385418974808[189] = 0.0;
   out_4137219385418974808[190] = 1.0;
   out_4137219385418974808[191] = 0.0;
   out_4137219385418974808[192] = 0.0;
   out_4137219385418974808[193] = 0.0;
   out_4137219385418974808[194] = 0.0;
   out_4137219385418974808[195] = 0.0;
   out_4137219385418974808[196] = 0.0;
   out_4137219385418974808[197] = 0.0;
   out_4137219385418974808[198] = 0.0;
   out_4137219385418974808[199] = 0.0;
   out_4137219385418974808[200] = 0.0;
   out_4137219385418974808[201] = 0.0;
   out_4137219385418974808[202] = 0.0;
   out_4137219385418974808[203] = 0.0;
   out_4137219385418974808[204] = 0.0;
   out_4137219385418974808[205] = 0.0;
   out_4137219385418974808[206] = 0.0;
   out_4137219385418974808[207] = 0.0;
   out_4137219385418974808[208] = 0.0;
   out_4137219385418974808[209] = 1.0;
   out_4137219385418974808[210] = 0.0;
   out_4137219385418974808[211] = 0.0;
   out_4137219385418974808[212] = 0.0;
   out_4137219385418974808[213] = 0.0;
   out_4137219385418974808[214] = 0.0;
   out_4137219385418974808[215] = 0.0;
   out_4137219385418974808[216] = 0.0;
   out_4137219385418974808[217] = 0.0;
   out_4137219385418974808[218] = 0.0;
   out_4137219385418974808[219] = 0.0;
   out_4137219385418974808[220] = 0.0;
   out_4137219385418974808[221] = 0.0;
   out_4137219385418974808[222] = 0.0;
   out_4137219385418974808[223] = 0.0;
   out_4137219385418974808[224] = 0.0;
   out_4137219385418974808[225] = 0.0;
   out_4137219385418974808[226] = 0.0;
   out_4137219385418974808[227] = 0.0;
   out_4137219385418974808[228] = 1.0;
   out_4137219385418974808[229] = 0.0;
   out_4137219385418974808[230] = 0.0;
   out_4137219385418974808[231] = 0.0;
   out_4137219385418974808[232] = 0.0;
   out_4137219385418974808[233] = 0.0;
   out_4137219385418974808[234] = 0.0;
   out_4137219385418974808[235] = 0.0;
   out_4137219385418974808[236] = 0.0;
   out_4137219385418974808[237] = 0.0;
   out_4137219385418974808[238] = 0.0;
   out_4137219385418974808[239] = 0.0;
   out_4137219385418974808[240] = 0.0;
   out_4137219385418974808[241] = 0.0;
   out_4137219385418974808[242] = 0.0;
   out_4137219385418974808[243] = 0.0;
   out_4137219385418974808[244] = 0.0;
   out_4137219385418974808[245] = 0.0;
   out_4137219385418974808[246] = 0.0;
   out_4137219385418974808[247] = 1.0;
   out_4137219385418974808[248] = 0.0;
   out_4137219385418974808[249] = 0.0;
   out_4137219385418974808[250] = 0.0;
   out_4137219385418974808[251] = 0.0;
   out_4137219385418974808[252] = 0.0;
   out_4137219385418974808[253] = 0.0;
   out_4137219385418974808[254] = 0.0;
   out_4137219385418974808[255] = 0.0;
   out_4137219385418974808[256] = 0.0;
   out_4137219385418974808[257] = 0.0;
   out_4137219385418974808[258] = 0.0;
   out_4137219385418974808[259] = 0.0;
   out_4137219385418974808[260] = 0.0;
   out_4137219385418974808[261] = 0.0;
   out_4137219385418974808[262] = 0.0;
   out_4137219385418974808[263] = 0.0;
   out_4137219385418974808[264] = 0.0;
   out_4137219385418974808[265] = 0.0;
   out_4137219385418974808[266] = 1.0;
   out_4137219385418974808[267] = 0.0;
   out_4137219385418974808[268] = 0.0;
   out_4137219385418974808[269] = 0.0;
   out_4137219385418974808[270] = 0.0;
   out_4137219385418974808[271] = 0.0;
   out_4137219385418974808[272] = 0.0;
   out_4137219385418974808[273] = 0.0;
   out_4137219385418974808[274] = 0.0;
   out_4137219385418974808[275] = 0.0;
   out_4137219385418974808[276] = 0.0;
   out_4137219385418974808[277] = 0.0;
   out_4137219385418974808[278] = 0.0;
   out_4137219385418974808[279] = 0.0;
   out_4137219385418974808[280] = 0.0;
   out_4137219385418974808[281] = 0.0;
   out_4137219385418974808[282] = 0.0;
   out_4137219385418974808[283] = 0.0;
   out_4137219385418974808[284] = 0.0;
   out_4137219385418974808[285] = 1.0;
   out_4137219385418974808[286] = 0.0;
   out_4137219385418974808[287] = 0.0;
   out_4137219385418974808[288] = 0.0;
   out_4137219385418974808[289] = 0.0;
   out_4137219385418974808[290] = 0.0;
   out_4137219385418974808[291] = 0.0;
   out_4137219385418974808[292] = 0.0;
   out_4137219385418974808[293] = 0.0;
   out_4137219385418974808[294] = 0.0;
   out_4137219385418974808[295] = 0.0;
   out_4137219385418974808[296] = 0.0;
   out_4137219385418974808[297] = 0.0;
   out_4137219385418974808[298] = 0.0;
   out_4137219385418974808[299] = 0.0;
   out_4137219385418974808[300] = 0.0;
   out_4137219385418974808[301] = 0.0;
   out_4137219385418974808[302] = 0.0;
   out_4137219385418974808[303] = 0.0;
   out_4137219385418974808[304] = 1.0;
   out_4137219385418974808[305] = 0.0;
   out_4137219385418974808[306] = 0.0;
   out_4137219385418974808[307] = 0.0;
   out_4137219385418974808[308] = 0.0;
   out_4137219385418974808[309] = 0.0;
   out_4137219385418974808[310] = 0.0;
   out_4137219385418974808[311] = 0.0;
   out_4137219385418974808[312] = 0.0;
   out_4137219385418974808[313] = 0.0;
   out_4137219385418974808[314] = 0.0;
   out_4137219385418974808[315] = 0.0;
   out_4137219385418974808[316] = 0.0;
   out_4137219385418974808[317] = 0.0;
   out_4137219385418974808[318] = 0.0;
   out_4137219385418974808[319] = 0.0;
   out_4137219385418974808[320] = 0.0;
   out_4137219385418974808[321] = 0.0;
   out_4137219385418974808[322] = 0.0;
   out_4137219385418974808[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1005410473172106637) {
   out_1005410473172106637[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1005410473172106637[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1005410473172106637[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1005410473172106637[3] = dt*state[12] + state[3];
   out_1005410473172106637[4] = dt*state[13] + state[4];
   out_1005410473172106637[5] = dt*state[14] + state[5];
   out_1005410473172106637[6] = state[6];
   out_1005410473172106637[7] = state[7];
   out_1005410473172106637[8] = state[8];
   out_1005410473172106637[9] = state[9];
   out_1005410473172106637[10] = state[10];
   out_1005410473172106637[11] = state[11];
   out_1005410473172106637[12] = state[12];
   out_1005410473172106637[13] = state[13];
   out_1005410473172106637[14] = state[14];
   out_1005410473172106637[15] = state[15];
   out_1005410473172106637[16] = state[16];
   out_1005410473172106637[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5217597012244076167) {
   out_5217597012244076167[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5217597012244076167[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5217597012244076167[2] = 0;
   out_5217597012244076167[3] = 0;
   out_5217597012244076167[4] = 0;
   out_5217597012244076167[5] = 0;
   out_5217597012244076167[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5217597012244076167[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5217597012244076167[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5217597012244076167[9] = 0;
   out_5217597012244076167[10] = 0;
   out_5217597012244076167[11] = 0;
   out_5217597012244076167[12] = 0;
   out_5217597012244076167[13] = 0;
   out_5217597012244076167[14] = 0;
   out_5217597012244076167[15] = 0;
   out_5217597012244076167[16] = 0;
   out_5217597012244076167[17] = 0;
   out_5217597012244076167[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5217597012244076167[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5217597012244076167[20] = 0;
   out_5217597012244076167[21] = 0;
   out_5217597012244076167[22] = 0;
   out_5217597012244076167[23] = 0;
   out_5217597012244076167[24] = 0;
   out_5217597012244076167[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5217597012244076167[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5217597012244076167[27] = 0;
   out_5217597012244076167[28] = 0;
   out_5217597012244076167[29] = 0;
   out_5217597012244076167[30] = 0;
   out_5217597012244076167[31] = 0;
   out_5217597012244076167[32] = 0;
   out_5217597012244076167[33] = 0;
   out_5217597012244076167[34] = 0;
   out_5217597012244076167[35] = 0;
   out_5217597012244076167[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5217597012244076167[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5217597012244076167[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5217597012244076167[39] = 0;
   out_5217597012244076167[40] = 0;
   out_5217597012244076167[41] = 0;
   out_5217597012244076167[42] = 0;
   out_5217597012244076167[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5217597012244076167[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5217597012244076167[45] = 0;
   out_5217597012244076167[46] = 0;
   out_5217597012244076167[47] = 0;
   out_5217597012244076167[48] = 0;
   out_5217597012244076167[49] = 0;
   out_5217597012244076167[50] = 0;
   out_5217597012244076167[51] = 0;
   out_5217597012244076167[52] = 0;
   out_5217597012244076167[53] = 0;
   out_5217597012244076167[54] = 0;
   out_5217597012244076167[55] = 0;
   out_5217597012244076167[56] = 0;
   out_5217597012244076167[57] = 1;
   out_5217597012244076167[58] = 0;
   out_5217597012244076167[59] = 0;
   out_5217597012244076167[60] = 0;
   out_5217597012244076167[61] = 0;
   out_5217597012244076167[62] = 0;
   out_5217597012244076167[63] = 0;
   out_5217597012244076167[64] = 0;
   out_5217597012244076167[65] = 0;
   out_5217597012244076167[66] = dt;
   out_5217597012244076167[67] = 0;
   out_5217597012244076167[68] = 0;
   out_5217597012244076167[69] = 0;
   out_5217597012244076167[70] = 0;
   out_5217597012244076167[71] = 0;
   out_5217597012244076167[72] = 0;
   out_5217597012244076167[73] = 0;
   out_5217597012244076167[74] = 0;
   out_5217597012244076167[75] = 0;
   out_5217597012244076167[76] = 1;
   out_5217597012244076167[77] = 0;
   out_5217597012244076167[78] = 0;
   out_5217597012244076167[79] = 0;
   out_5217597012244076167[80] = 0;
   out_5217597012244076167[81] = 0;
   out_5217597012244076167[82] = 0;
   out_5217597012244076167[83] = 0;
   out_5217597012244076167[84] = 0;
   out_5217597012244076167[85] = dt;
   out_5217597012244076167[86] = 0;
   out_5217597012244076167[87] = 0;
   out_5217597012244076167[88] = 0;
   out_5217597012244076167[89] = 0;
   out_5217597012244076167[90] = 0;
   out_5217597012244076167[91] = 0;
   out_5217597012244076167[92] = 0;
   out_5217597012244076167[93] = 0;
   out_5217597012244076167[94] = 0;
   out_5217597012244076167[95] = 1;
   out_5217597012244076167[96] = 0;
   out_5217597012244076167[97] = 0;
   out_5217597012244076167[98] = 0;
   out_5217597012244076167[99] = 0;
   out_5217597012244076167[100] = 0;
   out_5217597012244076167[101] = 0;
   out_5217597012244076167[102] = 0;
   out_5217597012244076167[103] = 0;
   out_5217597012244076167[104] = dt;
   out_5217597012244076167[105] = 0;
   out_5217597012244076167[106] = 0;
   out_5217597012244076167[107] = 0;
   out_5217597012244076167[108] = 0;
   out_5217597012244076167[109] = 0;
   out_5217597012244076167[110] = 0;
   out_5217597012244076167[111] = 0;
   out_5217597012244076167[112] = 0;
   out_5217597012244076167[113] = 0;
   out_5217597012244076167[114] = 1;
   out_5217597012244076167[115] = 0;
   out_5217597012244076167[116] = 0;
   out_5217597012244076167[117] = 0;
   out_5217597012244076167[118] = 0;
   out_5217597012244076167[119] = 0;
   out_5217597012244076167[120] = 0;
   out_5217597012244076167[121] = 0;
   out_5217597012244076167[122] = 0;
   out_5217597012244076167[123] = 0;
   out_5217597012244076167[124] = 0;
   out_5217597012244076167[125] = 0;
   out_5217597012244076167[126] = 0;
   out_5217597012244076167[127] = 0;
   out_5217597012244076167[128] = 0;
   out_5217597012244076167[129] = 0;
   out_5217597012244076167[130] = 0;
   out_5217597012244076167[131] = 0;
   out_5217597012244076167[132] = 0;
   out_5217597012244076167[133] = 1;
   out_5217597012244076167[134] = 0;
   out_5217597012244076167[135] = 0;
   out_5217597012244076167[136] = 0;
   out_5217597012244076167[137] = 0;
   out_5217597012244076167[138] = 0;
   out_5217597012244076167[139] = 0;
   out_5217597012244076167[140] = 0;
   out_5217597012244076167[141] = 0;
   out_5217597012244076167[142] = 0;
   out_5217597012244076167[143] = 0;
   out_5217597012244076167[144] = 0;
   out_5217597012244076167[145] = 0;
   out_5217597012244076167[146] = 0;
   out_5217597012244076167[147] = 0;
   out_5217597012244076167[148] = 0;
   out_5217597012244076167[149] = 0;
   out_5217597012244076167[150] = 0;
   out_5217597012244076167[151] = 0;
   out_5217597012244076167[152] = 1;
   out_5217597012244076167[153] = 0;
   out_5217597012244076167[154] = 0;
   out_5217597012244076167[155] = 0;
   out_5217597012244076167[156] = 0;
   out_5217597012244076167[157] = 0;
   out_5217597012244076167[158] = 0;
   out_5217597012244076167[159] = 0;
   out_5217597012244076167[160] = 0;
   out_5217597012244076167[161] = 0;
   out_5217597012244076167[162] = 0;
   out_5217597012244076167[163] = 0;
   out_5217597012244076167[164] = 0;
   out_5217597012244076167[165] = 0;
   out_5217597012244076167[166] = 0;
   out_5217597012244076167[167] = 0;
   out_5217597012244076167[168] = 0;
   out_5217597012244076167[169] = 0;
   out_5217597012244076167[170] = 0;
   out_5217597012244076167[171] = 1;
   out_5217597012244076167[172] = 0;
   out_5217597012244076167[173] = 0;
   out_5217597012244076167[174] = 0;
   out_5217597012244076167[175] = 0;
   out_5217597012244076167[176] = 0;
   out_5217597012244076167[177] = 0;
   out_5217597012244076167[178] = 0;
   out_5217597012244076167[179] = 0;
   out_5217597012244076167[180] = 0;
   out_5217597012244076167[181] = 0;
   out_5217597012244076167[182] = 0;
   out_5217597012244076167[183] = 0;
   out_5217597012244076167[184] = 0;
   out_5217597012244076167[185] = 0;
   out_5217597012244076167[186] = 0;
   out_5217597012244076167[187] = 0;
   out_5217597012244076167[188] = 0;
   out_5217597012244076167[189] = 0;
   out_5217597012244076167[190] = 1;
   out_5217597012244076167[191] = 0;
   out_5217597012244076167[192] = 0;
   out_5217597012244076167[193] = 0;
   out_5217597012244076167[194] = 0;
   out_5217597012244076167[195] = 0;
   out_5217597012244076167[196] = 0;
   out_5217597012244076167[197] = 0;
   out_5217597012244076167[198] = 0;
   out_5217597012244076167[199] = 0;
   out_5217597012244076167[200] = 0;
   out_5217597012244076167[201] = 0;
   out_5217597012244076167[202] = 0;
   out_5217597012244076167[203] = 0;
   out_5217597012244076167[204] = 0;
   out_5217597012244076167[205] = 0;
   out_5217597012244076167[206] = 0;
   out_5217597012244076167[207] = 0;
   out_5217597012244076167[208] = 0;
   out_5217597012244076167[209] = 1;
   out_5217597012244076167[210] = 0;
   out_5217597012244076167[211] = 0;
   out_5217597012244076167[212] = 0;
   out_5217597012244076167[213] = 0;
   out_5217597012244076167[214] = 0;
   out_5217597012244076167[215] = 0;
   out_5217597012244076167[216] = 0;
   out_5217597012244076167[217] = 0;
   out_5217597012244076167[218] = 0;
   out_5217597012244076167[219] = 0;
   out_5217597012244076167[220] = 0;
   out_5217597012244076167[221] = 0;
   out_5217597012244076167[222] = 0;
   out_5217597012244076167[223] = 0;
   out_5217597012244076167[224] = 0;
   out_5217597012244076167[225] = 0;
   out_5217597012244076167[226] = 0;
   out_5217597012244076167[227] = 0;
   out_5217597012244076167[228] = 1;
   out_5217597012244076167[229] = 0;
   out_5217597012244076167[230] = 0;
   out_5217597012244076167[231] = 0;
   out_5217597012244076167[232] = 0;
   out_5217597012244076167[233] = 0;
   out_5217597012244076167[234] = 0;
   out_5217597012244076167[235] = 0;
   out_5217597012244076167[236] = 0;
   out_5217597012244076167[237] = 0;
   out_5217597012244076167[238] = 0;
   out_5217597012244076167[239] = 0;
   out_5217597012244076167[240] = 0;
   out_5217597012244076167[241] = 0;
   out_5217597012244076167[242] = 0;
   out_5217597012244076167[243] = 0;
   out_5217597012244076167[244] = 0;
   out_5217597012244076167[245] = 0;
   out_5217597012244076167[246] = 0;
   out_5217597012244076167[247] = 1;
   out_5217597012244076167[248] = 0;
   out_5217597012244076167[249] = 0;
   out_5217597012244076167[250] = 0;
   out_5217597012244076167[251] = 0;
   out_5217597012244076167[252] = 0;
   out_5217597012244076167[253] = 0;
   out_5217597012244076167[254] = 0;
   out_5217597012244076167[255] = 0;
   out_5217597012244076167[256] = 0;
   out_5217597012244076167[257] = 0;
   out_5217597012244076167[258] = 0;
   out_5217597012244076167[259] = 0;
   out_5217597012244076167[260] = 0;
   out_5217597012244076167[261] = 0;
   out_5217597012244076167[262] = 0;
   out_5217597012244076167[263] = 0;
   out_5217597012244076167[264] = 0;
   out_5217597012244076167[265] = 0;
   out_5217597012244076167[266] = 1;
   out_5217597012244076167[267] = 0;
   out_5217597012244076167[268] = 0;
   out_5217597012244076167[269] = 0;
   out_5217597012244076167[270] = 0;
   out_5217597012244076167[271] = 0;
   out_5217597012244076167[272] = 0;
   out_5217597012244076167[273] = 0;
   out_5217597012244076167[274] = 0;
   out_5217597012244076167[275] = 0;
   out_5217597012244076167[276] = 0;
   out_5217597012244076167[277] = 0;
   out_5217597012244076167[278] = 0;
   out_5217597012244076167[279] = 0;
   out_5217597012244076167[280] = 0;
   out_5217597012244076167[281] = 0;
   out_5217597012244076167[282] = 0;
   out_5217597012244076167[283] = 0;
   out_5217597012244076167[284] = 0;
   out_5217597012244076167[285] = 1;
   out_5217597012244076167[286] = 0;
   out_5217597012244076167[287] = 0;
   out_5217597012244076167[288] = 0;
   out_5217597012244076167[289] = 0;
   out_5217597012244076167[290] = 0;
   out_5217597012244076167[291] = 0;
   out_5217597012244076167[292] = 0;
   out_5217597012244076167[293] = 0;
   out_5217597012244076167[294] = 0;
   out_5217597012244076167[295] = 0;
   out_5217597012244076167[296] = 0;
   out_5217597012244076167[297] = 0;
   out_5217597012244076167[298] = 0;
   out_5217597012244076167[299] = 0;
   out_5217597012244076167[300] = 0;
   out_5217597012244076167[301] = 0;
   out_5217597012244076167[302] = 0;
   out_5217597012244076167[303] = 0;
   out_5217597012244076167[304] = 1;
   out_5217597012244076167[305] = 0;
   out_5217597012244076167[306] = 0;
   out_5217597012244076167[307] = 0;
   out_5217597012244076167[308] = 0;
   out_5217597012244076167[309] = 0;
   out_5217597012244076167[310] = 0;
   out_5217597012244076167[311] = 0;
   out_5217597012244076167[312] = 0;
   out_5217597012244076167[313] = 0;
   out_5217597012244076167[314] = 0;
   out_5217597012244076167[315] = 0;
   out_5217597012244076167[316] = 0;
   out_5217597012244076167[317] = 0;
   out_5217597012244076167[318] = 0;
   out_5217597012244076167[319] = 0;
   out_5217597012244076167[320] = 0;
   out_5217597012244076167[321] = 0;
   out_5217597012244076167[322] = 0;
   out_5217597012244076167[323] = 1;
}
void h_4(double *state, double *unused, double *out_1497349936567297536) {
   out_1497349936567297536[0] = state[6] + state[9];
   out_1497349936567297536[1] = state[7] + state[10];
   out_1497349936567297536[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1129598351143808372) {
   out_1129598351143808372[0] = 0;
   out_1129598351143808372[1] = 0;
   out_1129598351143808372[2] = 0;
   out_1129598351143808372[3] = 0;
   out_1129598351143808372[4] = 0;
   out_1129598351143808372[5] = 0;
   out_1129598351143808372[6] = 1;
   out_1129598351143808372[7] = 0;
   out_1129598351143808372[8] = 0;
   out_1129598351143808372[9] = 1;
   out_1129598351143808372[10] = 0;
   out_1129598351143808372[11] = 0;
   out_1129598351143808372[12] = 0;
   out_1129598351143808372[13] = 0;
   out_1129598351143808372[14] = 0;
   out_1129598351143808372[15] = 0;
   out_1129598351143808372[16] = 0;
   out_1129598351143808372[17] = 0;
   out_1129598351143808372[18] = 0;
   out_1129598351143808372[19] = 0;
   out_1129598351143808372[20] = 0;
   out_1129598351143808372[21] = 0;
   out_1129598351143808372[22] = 0;
   out_1129598351143808372[23] = 0;
   out_1129598351143808372[24] = 0;
   out_1129598351143808372[25] = 1;
   out_1129598351143808372[26] = 0;
   out_1129598351143808372[27] = 0;
   out_1129598351143808372[28] = 1;
   out_1129598351143808372[29] = 0;
   out_1129598351143808372[30] = 0;
   out_1129598351143808372[31] = 0;
   out_1129598351143808372[32] = 0;
   out_1129598351143808372[33] = 0;
   out_1129598351143808372[34] = 0;
   out_1129598351143808372[35] = 0;
   out_1129598351143808372[36] = 0;
   out_1129598351143808372[37] = 0;
   out_1129598351143808372[38] = 0;
   out_1129598351143808372[39] = 0;
   out_1129598351143808372[40] = 0;
   out_1129598351143808372[41] = 0;
   out_1129598351143808372[42] = 0;
   out_1129598351143808372[43] = 0;
   out_1129598351143808372[44] = 1;
   out_1129598351143808372[45] = 0;
   out_1129598351143808372[46] = 0;
   out_1129598351143808372[47] = 1;
   out_1129598351143808372[48] = 0;
   out_1129598351143808372[49] = 0;
   out_1129598351143808372[50] = 0;
   out_1129598351143808372[51] = 0;
   out_1129598351143808372[52] = 0;
   out_1129598351143808372[53] = 0;
}
void h_10(double *state, double *unused, double *out_3534162960479099254) {
   out_3534162960479099254[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3534162960479099254[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3534162960479099254[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_240511820445146055) {
   out_240511820445146055[0] = 0;
   out_240511820445146055[1] = 9.8100000000000005*cos(state[1]);
   out_240511820445146055[2] = 0;
   out_240511820445146055[3] = 0;
   out_240511820445146055[4] = -state[8];
   out_240511820445146055[5] = state[7];
   out_240511820445146055[6] = 0;
   out_240511820445146055[7] = state[5];
   out_240511820445146055[8] = -state[4];
   out_240511820445146055[9] = 0;
   out_240511820445146055[10] = 0;
   out_240511820445146055[11] = 0;
   out_240511820445146055[12] = 1;
   out_240511820445146055[13] = 0;
   out_240511820445146055[14] = 0;
   out_240511820445146055[15] = 1;
   out_240511820445146055[16] = 0;
   out_240511820445146055[17] = 0;
   out_240511820445146055[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_240511820445146055[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_240511820445146055[20] = 0;
   out_240511820445146055[21] = state[8];
   out_240511820445146055[22] = 0;
   out_240511820445146055[23] = -state[6];
   out_240511820445146055[24] = -state[5];
   out_240511820445146055[25] = 0;
   out_240511820445146055[26] = state[3];
   out_240511820445146055[27] = 0;
   out_240511820445146055[28] = 0;
   out_240511820445146055[29] = 0;
   out_240511820445146055[30] = 0;
   out_240511820445146055[31] = 1;
   out_240511820445146055[32] = 0;
   out_240511820445146055[33] = 0;
   out_240511820445146055[34] = 1;
   out_240511820445146055[35] = 0;
   out_240511820445146055[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_240511820445146055[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_240511820445146055[38] = 0;
   out_240511820445146055[39] = -state[7];
   out_240511820445146055[40] = state[6];
   out_240511820445146055[41] = 0;
   out_240511820445146055[42] = state[4];
   out_240511820445146055[43] = -state[3];
   out_240511820445146055[44] = 0;
   out_240511820445146055[45] = 0;
   out_240511820445146055[46] = 0;
   out_240511820445146055[47] = 0;
   out_240511820445146055[48] = 0;
   out_240511820445146055[49] = 0;
   out_240511820445146055[50] = 1;
   out_240511820445146055[51] = 0;
   out_240511820445146055[52] = 0;
   out_240511820445146055[53] = 1;
}
void h_13(double *state, double *unused, double *out_2296308651892447689) {
   out_2296308651892447689[0] = state[3];
   out_2296308651892447689[1] = state[4];
   out_2296308651892447689[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6481032857172892557) {
   out_6481032857172892557[0] = 0;
   out_6481032857172892557[1] = 0;
   out_6481032857172892557[2] = 0;
   out_6481032857172892557[3] = 1;
   out_6481032857172892557[4] = 0;
   out_6481032857172892557[5] = 0;
   out_6481032857172892557[6] = 0;
   out_6481032857172892557[7] = 0;
   out_6481032857172892557[8] = 0;
   out_6481032857172892557[9] = 0;
   out_6481032857172892557[10] = 0;
   out_6481032857172892557[11] = 0;
   out_6481032857172892557[12] = 0;
   out_6481032857172892557[13] = 0;
   out_6481032857172892557[14] = 0;
   out_6481032857172892557[15] = 0;
   out_6481032857172892557[16] = 0;
   out_6481032857172892557[17] = 0;
   out_6481032857172892557[18] = 0;
   out_6481032857172892557[19] = 0;
   out_6481032857172892557[20] = 0;
   out_6481032857172892557[21] = 0;
   out_6481032857172892557[22] = 1;
   out_6481032857172892557[23] = 0;
   out_6481032857172892557[24] = 0;
   out_6481032857172892557[25] = 0;
   out_6481032857172892557[26] = 0;
   out_6481032857172892557[27] = 0;
   out_6481032857172892557[28] = 0;
   out_6481032857172892557[29] = 0;
   out_6481032857172892557[30] = 0;
   out_6481032857172892557[31] = 0;
   out_6481032857172892557[32] = 0;
   out_6481032857172892557[33] = 0;
   out_6481032857172892557[34] = 0;
   out_6481032857172892557[35] = 0;
   out_6481032857172892557[36] = 0;
   out_6481032857172892557[37] = 0;
   out_6481032857172892557[38] = 0;
   out_6481032857172892557[39] = 0;
   out_6481032857172892557[40] = 0;
   out_6481032857172892557[41] = 1;
   out_6481032857172892557[42] = 0;
   out_6481032857172892557[43] = 0;
   out_6481032857172892557[44] = 0;
   out_6481032857172892557[45] = 0;
   out_6481032857172892557[46] = 0;
   out_6481032857172892557[47] = 0;
   out_6481032857172892557[48] = 0;
   out_6481032857172892557[49] = 0;
   out_6481032857172892557[50] = 0;
   out_6481032857172892557[51] = 0;
   out_6481032857172892557[52] = 0;
   out_6481032857172892557[53] = 0;
}
void h_14(double *state, double *unused, double *out_5180046062651358956) {
   out_5180046062651358956[0] = state[6];
   out_5180046062651358956[1] = state[7];
   out_5180046062651358956[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2833642505195676157) {
   out_2833642505195676157[0] = 0;
   out_2833642505195676157[1] = 0;
   out_2833642505195676157[2] = 0;
   out_2833642505195676157[3] = 0;
   out_2833642505195676157[4] = 0;
   out_2833642505195676157[5] = 0;
   out_2833642505195676157[6] = 1;
   out_2833642505195676157[7] = 0;
   out_2833642505195676157[8] = 0;
   out_2833642505195676157[9] = 0;
   out_2833642505195676157[10] = 0;
   out_2833642505195676157[11] = 0;
   out_2833642505195676157[12] = 0;
   out_2833642505195676157[13] = 0;
   out_2833642505195676157[14] = 0;
   out_2833642505195676157[15] = 0;
   out_2833642505195676157[16] = 0;
   out_2833642505195676157[17] = 0;
   out_2833642505195676157[18] = 0;
   out_2833642505195676157[19] = 0;
   out_2833642505195676157[20] = 0;
   out_2833642505195676157[21] = 0;
   out_2833642505195676157[22] = 0;
   out_2833642505195676157[23] = 0;
   out_2833642505195676157[24] = 0;
   out_2833642505195676157[25] = 1;
   out_2833642505195676157[26] = 0;
   out_2833642505195676157[27] = 0;
   out_2833642505195676157[28] = 0;
   out_2833642505195676157[29] = 0;
   out_2833642505195676157[30] = 0;
   out_2833642505195676157[31] = 0;
   out_2833642505195676157[32] = 0;
   out_2833642505195676157[33] = 0;
   out_2833642505195676157[34] = 0;
   out_2833642505195676157[35] = 0;
   out_2833642505195676157[36] = 0;
   out_2833642505195676157[37] = 0;
   out_2833642505195676157[38] = 0;
   out_2833642505195676157[39] = 0;
   out_2833642505195676157[40] = 0;
   out_2833642505195676157[41] = 0;
   out_2833642505195676157[42] = 0;
   out_2833642505195676157[43] = 0;
   out_2833642505195676157[44] = 1;
   out_2833642505195676157[45] = 0;
   out_2833642505195676157[46] = 0;
   out_2833642505195676157[47] = 0;
   out_2833642505195676157[48] = 0;
   out_2833642505195676157[49] = 0;
   out_2833642505195676157[50] = 0;
   out_2833642505195676157[51] = 0;
   out_2833642505195676157[52] = 0;
   out_2833642505195676157[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_6893490668885513914) {
  err_fun(nom_x, delta_x, out_6893490668885513914);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4691374393904796900) {
  inv_err_fun(nom_x, true_x, out_4691374393904796900);
}
void pose_H_mod_fun(double *state, double *out_4137219385418974808) {
  H_mod_fun(state, out_4137219385418974808);
}
void pose_f_fun(double *state, double dt, double *out_1005410473172106637) {
  f_fun(state,  dt, out_1005410473172106637);
}
void pose_F_fun(double *state, double dt, double *out_5217597012244076167) {
  F_fun(state,  dt, out_5217597012244076167);
}
void pose_h_4(double *state, double *unused, double *out_1497349936567297536) {
  h_4(state, unused, out_1497349936567297536);
}
void pose_H_4(double *state, double *unused, double *out_1129598351143808372) {
  H_4(state, unused, out_1129598351143808372);
}
void pose_h_10(double *state, double *unused, double *out_3534162960479099254) {
  h_10(state, unused, out_3534162960479099254);
}
void pose_H_10(double *state, double *unused, double *out_240511820445146055) {
  H_10(state, unused, out_240511820445146055);
}
void pose_h_13(double *state, double *unused, double *out_2296308651892447689) {
  h_13(state, unused, out_2296308651892447689);
}
void pose_H_13(double *state, double *unused, double *out_6481032857172892557) {
  H_13(state, unused, out_6481032857172892557);
}
void pose_h_14(double *state, double *unused, double *out_5180046062651358956) {
  h_14(state, unused, out_5180046062651358956);
}
void pose_H_14(double *state, double *unused, double *out_2833642505195676157) {
  H_14(state, unused, out_2833642505195676157);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
