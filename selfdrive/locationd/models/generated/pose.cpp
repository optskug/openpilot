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
void err_fun(double *nom_x, double *delta_x, double *out_7224170274929451769) {
   out_7224170274929451769[0] = delta_x[0] + nom_x[0];
   out_7224170274929451769[1] = delta_x[1] + nom_x[1];
   out_7224170274929451769[2] = delta_x[2] + nom_x[2];
   out_7224170274929451769[3] = delta_x[3] + nom_x[3];
   out_7224170274929451769[4] = delta_x[4] + nom_x[4];
   out_7224170274929451769[5] = delta_x[5] + nom_x[5];
   out_7224170274929451769[6] = delta_x[6] + nom_x[6];
   out_7224170274929451769[7] = delta_x[7] + nom_x[7];
   out_7224170274929451769[8] = delta_x[8] + nom_x[8];
   out_7224170274929451769[9] = delta_x[9] + nom_x[9];
   out_7224170274929451769[10] = delta_x[10] + nom_x[10];
   out_7224170274929451769[11] = delta_x[11] + nom_x[11];
   out_7224170274929451769[12] = delta_x[12] + nom_x[12];
   out_7224170274929451769[13] = delta_x[13] + nom_x[13];
   out_7224170274929451769[14] = delta_x[14] + nom_x[14];
   out_7224170274929451769[15] = delta_x[15] + nom_x[15];
   out_7224170274929451769[16] = delta_x[16] + nom_x[16];
   out_7224170274929451769[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_580510085257942810) {
   out_580510085257942810[0] = -nom_x[0] + true_x[0];
   out_580510085257942810[1] = -nom_x[1] + true_x[1];
   out_580510085257942810[2] = -nom_x[2] + true_x[2];
   out_580510085257942810[3] = -nom_x[3] + true_x[3];
   out_580510085257942810[4] = -nom_x[4] + true_x[4];
   out_580510085257942810[5] = -nom_x[5] + true_x[5];
   out_580510085257942810[6] = -nom_x[6] + true_x[6];
   out_580510085257942810[7] = -nom_x[7] + true_x[7];
   out_580510085257942810[8] = -nom_x[8] + true_x[8];
   out_580510085257942810[9] = -nom_x[9] + true_x[9];
   out_580510085257942810[10] = -nom_x[10] + true_x[10];
   out_580510085257942810[11] = -nom_x[11] + true_x[11];
   out_580510085257942810[12] = -nom_x[12] + true_x[12];
   out_580510085257942810[13] = -nom_x[13] + true_x[13];
   out_580510085257942810[14] = -nom_x[14] + true_x[14];
   out_580510085257942810[15] = -nom_x[15] + true_x[15];
   out_580510085257942810[16] = -nom_x[16] + true_x[16];
   out_580510085257942810[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7521149564861609621) {
   out_7521149564861609621[0] = 1.0;
   out_7521149564861609621[1] = 0.0;
   out_7521149564861609621[2] = 0.0;
   out_7521149564861609621[3] = 0.0;
   out_7521149564861609621[4] = 0.0;
   out_7521149564861609621[5] = 0.0;
   out_7521149564861609621[6] = 0.0;
   out_7521149564861609621[7] = 0.0;
   out_7521149564861609621[8] = 0.0;
   out_7521149564861609621[9] = 0.0;
   out_7521149564861609621[10] = 0.0;
   out_7521149564861609621[11] = 0.0;
   out_7521149564861609621[12] = 0.0;
   out_7521149564861609621[13] = 0.0;
   out_7521149564861609621[14] = 0.0;
   out_7521149564861609621[15] = 0.0;
   out_7521149564861609621[16] = 0.0;
   out_7521149564861609621[17] = 0.0;
   out_7521149564861609621[18] = 0.0;
   out_7521149564861609621[19] = 1.0;
   out_7521149564861609621[20] = 0.0;
   out_7521149564861609621[21] = 0.0;
   out_7521149564861609621[22] = 0.0;
   out_7521149564861609621[23] = 0.0;
   out_7521149564861609621[24] = 0.0;
   out_7521149564861609621[25] = 0.0;
   out_7521149564861609621[26] = 0.0;
   out_7521149564861609621[27] = 0.0;
   out_7521149564861609621[28] = 0.0;
   out_7521149564861609621[29] = 0.0;
   out_7521149564861609621[30] = 0.0;
   out_7521149564861609621[31] = 0.0;
   out_7521149564861609621[32] = 0.0;
   out_7521149564861609621[33] = 0.0;
   out_7521149564861609621[34] = 0.0;
   out_7521149564861609621[35] = 0.0;
   out_7521149564861609621[36] = 0.0;
   out_7521149564861609621[37] = 0.0;
   out_7521149564861609621[38] = 1.0;
   out_7521149564861609621[39] = 0.0;
   out_7521149564861609621[40] = 0.0;
   out_7521149564861609621[41] = 0.0;
   out_7521149564861609621[42] = 0.0;
   out_7521149564861609621[43] = 0.0;
   out_7521149564861609621[44] = 0.0;
   out_7521149564861609621[45] = 0.0;
   out_7521149564861609621[46] = 0.0;
   out_7521149564861609621[47] = 0.0;
   out_7521149564861609621[48] = 0.0;
   out_7521149564861609621[49] = 0.0;
   out_7521149564861609621[50] = 0.0;
   out_7521149564861609621[51] = 0.0;
   out_7521149564861609621[52] = 0.0;
   out_7521149564861609621[53] = 0.0;
   out_7521149564861609621[54] = 0.0;
   out_7521149564861609621[55] = 0.0;
   out_7521149564861609621[56] = 0.0;
   out_7521149564861609621[57] = 1.0;
   out_7521149564861609621[58] = 0.0;
   out_7521149564861609621[59] = 0.0;
   out_7521149564861609621[60] = 0.0;
   out_7521149564861609621[61] = 0.0;
   out_7521149564861609621[62] = 0.0;
   out_7521149564861609621[63] = 0.0;
   out_7521149564861609621[64] = 0.0;
   out_7521149564861609621[65] = 0.0;
   out_7521149564861609621[66] = 0.0;
   out_7521149564861609621[67] = 0.0;
   out_7521149564861609621[68] = 0.0;
   out_7521149564861609621[69] = 0.0;
   out_7521149564861609621[70] = 0.0;
   out_7521149564861609621[71] = 0.0;
   out_7521149564861609621[72] = 0.0;
   out_7521149564861609621[73] = 0.0;
   out_7521149564861609621[74] = 0.0;
   out_7521149564861609621[75] = 0.0;
   out_7521149564861609621[76] = 1.0;
   out_7521149564861609621[77] = 0.0;
   out_7521149564861609621[78] = 0.0;
   out_7521149564861609621[79] = 0.0;
   out_7521149564861609621[80] = 0.0;
   out_7521149564861609621[81] = 0.0;
   out_7521149564861609621[82] = 0.0;
   out_7521149564861609621[83] = 0.0;
   out_7521149564861609621[84] = 0.0;
   out_7521149564861609621[85] = 0.0;
   out_7521149564861609621[86] = 0.0;
   out_7521149564861609621[87] = 0.0;
   out_7521149564861609621[88] = 0.0;
   out_7521149564861609621[89] = 0.0;
   out_7521149564861609621[90] = 0.0;
   out_7521149564861609621[91] = 0.0;
   out_7521149564861609621[92] = 0.0;
   out_7521149564861609621[93] = 0.0;
   out_7521149564861609621[94] = 0.0;
   out_7521149564861609621[95] = 1.0;
   out_7521149564861609621[96] = 0.0;
   out_7521149564861609621[97] = 0.0;
   out_7521149564861609621[98] = 0.0;
   out_7521149564861609621[99] = 0.0;
   out_7521149564861609621[100] = 0.0;
   out_7521149564861609621[101] = 0.0;
   out_7521149564861609621[102] = 0.0;
   out_7521149564861609621[103] = 0.0;
   out_7521149564861609621[104] = 0.0;
   out_7521149564861609621[105] = 0.0;
   out_7521149564861609621[106] = 0.0;
   out_7521149564861609621[107] = 0.0;
   out_7521149564861609621[108] = 0.0;
   out_7521149564861609621[109] = 0.0;
   out_7521149564861609621[110] = 0.0;
   out_7521149564861609621[111] = 0.0;
   out_7521149564861609621[112] = 0.0;
   out_7521149564861609621[113] = 0.0;
   out_7521149564861609621[114] = 1.0;
   out_7521149564861609621[115] = 0.0;
   out_7521149564861609621[116] = 0.0;
   out_7521149564861609621[117] = 0.0;
   out_7521149564861609621[118] = 0.0;
   out_7521149564861609621[119] = 0.0;
   out_7521149564861609621[120] = 0.0;
   out_7521149564861609621[121] = 0.0;
   out_7521149564861609621[122] = 0.0;
   out_7521149564861609621[123] = 0.0;
   out_7521149564861609621[124] = 0.0;
   out_7521149564861609621[125] = 0.0;
   out_7521149564861609621[126] = 0.0;
   out_7521149564861609621[127] = 0.0;
   out_7521149564861609621[128] = 0.0;
   out_7521149564861609621[129] = 0.0;
   out_7521149564861609621[130] = 0.0;
   out_7521149564861609621[131] = 0.0;
   out_7521149564861609621[132] = 0.0;
   out_7521149564861609621[133] = 1.0;
   out_7521149564861609621[134] = 0.0;
   out_7521149564861609621[135] = 0.0;
   out_7521149564861609621[136] = 0.0;
   out_7521149564861609621[137] = 0.0;
   out_7521149564861609621[138] = 0.0;
   out_7521149564861609621[139] = 0.0;
   out_7521149564861609621[140] = 0.0;
   out_7521149564861609621[141] = 0.0;
   out_7521149564861609621[142] = 0.0;
   out_7521149564861609621[143] = 0.0;
   out_7521149564861609621[144] = 0.0;
   out_7521149564861609621[145] = 0.0;
   out_7521149564861609621[146] = 0.0;
   out_7521149564861609621[147] = 0.0;
   out_7521149564861609621[148] = 0.0;
   out_7521149564861609621[149] = 0.0;
   out_7521149564861609621[150] = 0.0;
   out_7521149564861609621[151] = 0.0;
   out_7521149564861609621[152] = 1.0;
   out_7521149564861609621[153] = 0.0;
   out_7521149564861609621[154] = 0.0;
   out_7521149564861609621[155] = 0.0;
   out_7521149564861609621[156] = 0.0;
   out_7521149564861609621[157] = 0.0;
   out_7521149564861609621[158] = 0.0;
   out_7521149564861609621[159] = 0.0;
   out_7521149564861609621[160] = 0.0;
   out_7521149564861609621[161] = 0.0;
   out_7521149564861609621[162] = 0.0;
   out_7521149564861609621[163] = 0.0;
   out_7521149564861609621[164] = 0.0;
   out_7521149564861609621[165] = 0.0;
   out_7521149564861609621[166] = 0.0;
   out_7521149564861609621[167] = 0.0;
   out_7521149564861609621[168] = 0.0;
   out_7521149564861609621[169] = 0.0;
   out_7521149564861609621[170] = 0.0;
   out_7521149564861609621[171] = 1.0;
   out_7521149564861609621[172] = 0.0;
   out_7521149564861609621[173] = 0.0;
   out_7521149564861609621[174] = 0.0;
   out_7521149564861609621[175] = 0.0;
   out_7521149564861609621[176] = 0.0;
   out_7521149564861609621[177] = 0.0;
   out_7521149564861609621[178] = 0.0;
   out_7521149564861609621[179] = 0.0;
   out_7521149564861609621[180] = 0.0;
   out_7521149564861609621[181] = 0.0;
   out_7521149564861609621[182] = 0.0;
   out_7521149564861609621[183] = 0.0;
   out_7521149564861609621[184] = 0.0;
   out_7521149564861609621[185] = 0.0;
   out_7521149564861609621[186] = 0.0;
   out_7521149564861609621[187] = 0.0;
   out_7521149564861609621[188] = 0.0;
   out_7521149564861609621[189] = 0.0;
   out_7521149564861609621[190] = 1.0;
   out_7521149564861609621[191] = 0.0;
   out_7521149564861609621[192] = 0.0;
   out_7521149564861609621[193] = 0.0;
   out_7521149564861609621[194] = 0.0;
   out_7521149564861609621[195] = 0.0;
   out_7521149564861609621[196] = 0.0;
   out_7521149564861609621[197] = 0.0;
   out_7521149564861609621[198] = 0.0;
   out_7521149564861609621[199] = 0.0;
   out_7521149564861609621[200] = 0.0;
   out_7521149564861609621[201] = 0.0;
   out_7521149564861609621[202] = 0.0;
   out_7521149564861609621[203] = 0.0;
   out_7521149564861609621[204] = 0.0;
   out_7521149564861609621[205] = 0.0;
   out_7521149564861609621[206] = 0.0;
   out_7521149564861609621[207] = 0.0;
   out_7521149564861609621[208] = 0.0;
   out_7521149564861609621[209] = 1.0;
   out_7521149564861609621[210] = 0.0;
   out_7521149564861609621[211] = 0.0;
   out_7521149564861609621[212] = 0.0;
   out_7521149564861609621[213] = 0.0;
   out_7521149564861609621[214] = 0.0;
   out_7521149564861609621[215] = 0.0;
   out_7521149564861609621[216] = 0.0;
   out_7521149564861609621[217] = 0.0;
   out_7521149564861609621[218] = 0.0;
   out_7521149564861609621[219] = 0.0;
   out_7521149564861609621[220] = 0.0;
   out_7521149564861609621[221] = 0.0;
   out_7521149564861609621[222] = 0.0;
   out_7521149564861609621[223] = 0.0;
   out_7521149564861609621[224] = 0.0;
   out_7521149564861609621[225] = 0.0;
   out_7521149564861609621[226] = 0.0;
   out_7521149564861609621[227] = 0.0;
   out_7521149564861609621[228] = 1.0;
   out_7521149564861609621[229] = 0.0;
   out_7521149564861609621[230] = 0.0;
   out_7521149564861609621[231] = 0.0;
   out_7521149564861609621[232] = 0.0;
   out_7521149564861609621[233] = 0.0;
   out_7521149564861609621[234] = 0.0;
   out_7521149564861609621[235] = 0.0;
   out_7521149564861609621[236] = 0.0;
   out_7521149564861609621[237] = 0.0;
   out_7521149564861609621[238] = 0.0;
   out_7521149564861609621[239] = 0.0;
   out_7521149564861609621[240] = 0.0;
   out_7521149564861609621[241] = 0.0;
   out_7521149564861609621[242] = 0.0;
   out_7521149564861609621[243] = 0.0;
   out_7521149564861609621[244] = 0.0;
   out_7521149564861609621[245] = 0.0;
   out_7521149564861609621[246] = 0.0;
   out_7521149564861609621[247] = 1.0;
   out_7521149564861609621[248] = 0.0;
   out_7521149564861609621[249] = 0.0;
   out_7521149564861609621[250] = 0.0;
   out_7521149564861609621[251] = 0.0;
   out_7521149564861609621[252] = 0.0;
   out_7521149564861609621[253] = 0.0;
   out_7521149564861609621[254] = 0.0;
   out_7521149564861609621[255] = 0.0;
   out_7521149564861609621[256] = 0.0;
   out_7521149564861609621[257] = 0.0;
   out_7521149564861609621[258] = 0.0;
   out_7521149564861609621[259] = 0.0;
   out_7521149564861609621[260] = 0.0;
   out_7521149564861609621[261] = 0.0;
   out_7521149564861609621[262] = 0.0;
   out_7521149564861609621[263] = 0.0;
   out_7521149564861609621[264] = 0.0;
   out_7521149564861609621[265] = 0.0;
   out_7521149564861609621[266] = 1.0;
   out_7521149564861609621[267] = 0.0;
   out_7521149564861609621[268] = 0.0;
   out_7521149564861609621[269] = 0.0;
   out_7521149564861609621[270] = 0.0;
   out_7521149564861609621[271] = 0.0;
   out_7521149564861609621[272] = 0.0;
   out_7521149564861609621[273] = 0.0;
   out_7521149564861609621[274] = 0.0;
   out_7521149564861609621[275] = 0.0;
   out_7521149564861609621[276] = 0.0;
   out_7521149564861609621[277] = 0.0;
   out_7521149564861609621[278] = 0.0;
   out_7521149564861609621[279] = 0.0;
   out_7521149564861609621[280] = 0.0;
   out_7521149564861609621[281] = 0.0;
   out_7521149564861609621[282] = 0.0;
   out_7521149564861609621[283] = 0.0;
   out_7521149564861609621[284] = 0.0;
   out_7521149564861609621[285] = 1.0;
   out_7521149564861609621[286] = 0.0;
   out_7521149564861609621[287] = 0.0;
   out_7521149564861609621[288] = 0.0;
   out_7521149564861609621[289] = 0.0;
   out_7521149564861609621[290] = 0.0;
   out_7521149564861609621[291] = 0.0;
   out_7521149564861609621[292] = 0.0;
   out_7521149564861609621[293] = 0.0;
   out_7521149564861609621[294] = 0.0;
   out_7521149564861609621[295] = 0.0;
   out_7521149564861609621[296] = 0.0;
   out_7521149564861609621[297] = 0.0;
   out_7521149564861609621[298] = 0.0;
   out_7521149564861609621[299] = 0.0;
   out_7521149564861609621[300] = 0.0;
   out_7521149564861609621[301] = 0.0;
   out_7521149564861609621[302] = 0.0;
   out_7521149564861609621[303] = 0.0;
   out_7521149564861609621[304] = 1.0;
   out_7521149564861609621[305] = 0.0;
   out_7521149564861609621[306] = 0.0;
   out_7521149564861609621[307] = 0.0;
   out_7521149564861609621[308] = 0.0;
   out_7521149564861609621[309] = 0.0;
   out_7521149564861609621[310] = 0.0;
   out_7521149564861609621[311] = 0.0;
   out_7521149564861609621[312] = 0.0;
   out_7521149564861609621[313] = 0.0;
   out_7521149564861609621[314] = 0.0;
   out_7521149564861609621[315] = 0.0;
   out_7521149564861609621[316] = 0.0;
   out_7521149564861609621[317] = 0.0;
   out_7521149564861609621[318] = 0.0;
   out_7521149564861609621[319] = 0.0;
   out_7521149564861609621[320] = 0.0;
   out_7521149564861609621[321] = 0.0;
   out_7521149564861609621[322] = 0.0;
   out_7521149564861609621[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5784399927549256008) {
   out_5784399927549256008[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5784399927549256008[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5784399927549256008[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5784399927549256008[3] = dt*state[12] + state[3];
   out_5784399927549256008[4] = dt*state[13] + state[4];
   out_5784399927549256008[5] = dt*state[14] + state[5];
   out_5784399927549256008[6] = state[6];
   out_5784399927549256008[7] = state[7];
   out_5784399927549256008[8] = state[8];
   out_5784399927549256008[9] = state[9];
   out_5784399927549256008[10] = state[10];
   out_5784399927549256008[11] = state[11];
   out_5784399927549256008[12] = state[12];
   out_5784399927549256008[13] = state[13];
   out_5784399927549256008[14] = state[14];
   out_5784399927549256008[15] = state[15];
   out_5784399927549256008[16] = state[16];
   out_5784399927549256008[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7477745333434750070) {
   out_7477745333434750070[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7477745333434750070[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7477745333434750070[2] = 0;
   out_7477745333434750070[3] = 0;
   out_7477745333434750070[4] = 0;
   out_7477745333434750070[5] = 0;
   out_7477745333434750070[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7477745333434750070[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7477745333434750070[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7477745333434750070[9] = 0;
   out_7477745333434750070[10] = 0;
   out_7477745333434750070[11] = 0;
   out_7477745333434750070[12] = 0;
   out_7477745333434750070[13] = 0;
   out_7477745333434750070[14] = 0;
   out_7477745333434750070[15] = 0;
   out_7477745333434750070[16] = 0;
   out_7477745333434750070[17] = 0;
   out_7477745333434750070[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7477745333434750070[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7477745333434750070[20] = 0;
   out_7477745333434750070[21] = 0;
   out_7477745333434750070[22] = 0;
   out_7477745333434750070[23] = 0;
   out_7477745333434750070[24] = 0;
   out_7477745333434750070[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7477745333434750070[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7477745333434750070[27] = 0;
   out_7477745333434750070[28] = 0;
   out_7477745333434750070[29] = 0;
   out_7477745333434750070[30] = 0;
   out_7477745333434750070[31] = 0;
   out_7477745333434750070[32] = 0;
   out_7477745333434750070[33] = 0;
   out_7477745333434750070[34] = 0;
   out_7477745333434750070[35] = 0;
   out_7477745333434750070[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7477745333434750070[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7477745333434750070[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7477745333434750070[39] = 0;
   out_7477745333434750070[40] = 0;
   out_7477745333434750070[41] = 0;
   out_7477745333434750070[42] = 0;
   out_7477745333434750070[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7477745333434750070[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7477745333434750070[45] = 0;
   out_7477745333434750070[46] = 0;
   out_7477745333434750070[47] = 0;
   out_7477745333434750070[48] = 0;
   out_7477745333434750070[49] = 0;
   out_7477745333434750070[50] = 0;
   out_7477745333434750070[51] = 0;
   out_7477745333434750070[52] = 0;
   out_7477745333434750070[53] = 0;
   out_7477745333434750070[54] = 0;
   out_7477745333434750070[55] = 0;
   out_7477745333434750070[56] = 0;
   out_7477745333434750070[57] = 1;
   out_7477745333434750070[58] = 0;
   out_7477745333434750070[59] = 0;
   out_7477745333434750070[60] = 0;
   out_7477745333434750070[61] = 0;
   out_7477745333434750070[62] = 0;
   out_7477745333434750070[63] = 0;
   out_7477745333434750070[64] = 0;
   out_7477745333434750070[65] = 0;
   out_7477745333434750070[66] = dt;
   out_7477745333434750070[67] = 0;
   out_7477745333434750070[68] = 0;
   out_7477745333434750070[69] = 0;
   out_7477745333434750070[70] = 0;
   out_7477745333434750070[71] = 0;
   out_7477745333434750070[72] = 0;
   out_7477745333434750070[73] = 0;
   out_7477745333434750070[74] = 0;
   out_7477745333434750070[75] = 0;
   out_7477745333434750070[76] = 1;
   out_7477745333434750070[77] = 0;
   out_7477745333434750070[78] = 0;
   out_7477745333434750070[79] = 0;
   out_7477745333434750070[80] = 0;
   out_7477745333434750070[81] = 0;
   out_7477745333434750070[82] = 0;
   out_7477745333434750070[83] = 0;
   out_7477745333434750070[84] = 0;
   out_7477745333434750070[85] = dt;
   out_7477745333434750070[86] = 0;
   out_7477745333434750070[87] = 0;
   out_7477745333434750070[88] = 0;
   out_7477745333434750070[89] = 0;
   out_7477745333434750070[90] = 0;
   out_7477745333434750070[91] = 0;
   out_7477745333434750070[92] = 0;
   out_7477745333434750070[93] = 0;
   out_7477745333434750070[94] = 0;
   out_7477745333434750070[95] = 1;
   out_7477745333434750070[96] = 0;
   out_7477745333434750070[97] = 0;
   out_7477745333434750070[98] = 0;
   out_7477745333434750070[99] = 0;
   out_7477745333434750070[100] = 0;
   out_7477745333434750070[101] = 0;
   out_7477745333434750070[102] = 0;
   out_7477745333434750070[103] = 0;
   out_7477745333434750070[104] = dt;
   out_7477745333434750070[105] = 0;
   out_7477745333434750070[106] = 0;
   out_7477745333434750070[107] = 0;
   out_7477745333434750070[108] = 0;
   out_7477745333434750070[109] = 0;
   out_7477745333434750070[110] = 0;
   out_7477745333434750070[111] = 0;
   out_7477745333434750070[112] = 0;
   out_7477745333434750070[113] = 0;
   out_7477745333434750070[114] = 1;
   out_7477745333434750070[115] = 0;
   out_7477745333434750070[116] = 0;
   out_7477745333434750070[117] = 0;
   out_7477745333434750070[118] = 0;
   out_7477745333434750070[119] = 0;
   out_7477745333434750070[120] = 0;
   out_7477745333434750070[121] = 0;
   out_7477745333434750070[122] = 0;
   out_7477745333434750070[123] = 0;
   out_7477745333434750070[124] = 0;
   out_7477745333434750070[125] = 0;
   out_7477745333434750070[126] = 0;
   out_7477745333434750070[127] = 0;
   out_7477745333434750070[128] = 0;
   out_7477745333434750070[129] = 0;
   out_7477745333434750070[130] = 0;
   out_7477745333434750070[131] = 0;
   out_7477745333434750070[132] = 0;
   out_7477745333434750070[133] = 1;
   out_7477745333434750070[134] = 0;
   out_7477745333434750070[135] = 0;
   out_7477745333434750070[136] = 0;
   out_7477745333434750070[137] = 0;
   out_7477745333434750070[138] = 0;
   out_7477745333434750070[139] = 0;
   out_7477745333434750070[140] = 0;
   out_7477745333434750070[141] = 0;
   out_7477745333434750070[142] = 0;
   out_7477745333434750070[143] = 0;
   out_7477745333434750070[144] = 0;
   out_7477745333434750070[145] = 0;
   out_7477745333434750070[146] = 0;
   out_7477745333434750070[147] = 0;
   out_7477745333434750070[148] = 0;
   out_7477745333434750070[149] = 0;
   out_7477745333434750070[150] = 0;
   out_7477745333434750070[151] = 0;
   out_7477745333434750070[152] = 1;
   out_7477745333434750070[153] = 0;
   out_7477745333434750070[154] = 0;
   out_7477745333434750070[155] = 0;
   out_7477745333434750070[156] = 0;
   out_7477745333434750070[157] = 0;
   out_7477745333434750070[158] = 0;
   out_7477745333434750070[159] = 0;
   out_7477745333434750070[160] = 0;
   out_7477745333434750070[161] = 0;
   out_7477745333434750070[162] = 0;
   out_7477745333434750070[163] = 0;
   out_7477745333434750070[164] = 0;
   out_7477745333434750070[165] = 0;
   out_7477745333434750070[166] = 0;
   out_7477745333434750070[167] = 0;
   out_7477745333434750070[168] = 0;
   out_7477745333434750070[169] = 0;
   out_7477745333434750070[170] = 0;
   out_7477745333434750070[171] = 1;
   out_7477745333434750070[172] = 0;
   out_7477745333434750070[173] = 0;
   out_7477745333434750070[174] = 0;
   out_7477745333434750070[175] = 0;
   out_7477745333434750070[176] = 0;
   out_7477745333434750070[177] = 0;
   out_7477745333434750070[178] = 0;
   out_7477745333434750070[179] = 0;
   out_7477745333434750070[180] = 0;
   out_7477745333434750070[181] = 0;
   out_7477745333434750070[182] = 0;
   out_7477745333434750070[183] = 0;
   out_7477745333434750070[184] = 0;
   out_7477745333434750070[185] = 0;
   out_7477745333434750070[186] = 0;
   out_7477745333434750070[187] = 0;
   out_7477745333434750070[188] = 0;
   out_7477745333434750070[189] = 0;
   out_7477745333434750070[190] = 1;
   out_7477745333434750070[191] = 0;
   out_7477745333434750070[192] = 0;
   out_7477745333434750070[193] = 0;
   out_7477745333434750070[194] = 0;
   out_7477745333434750070[195] = 0;
   out_7477745333434750070[196] = 0;
   out_7477745333434750070[197] = 0;
   out_7477745333434750070[198] = 0;
   out_7477745333434750070[199] = 0;
   out_7477745333434750070[200] = 0;
   out_7477745333434750070[201] = 0;
   out_7477745333434750070[202] = 0;
   out_7477745333434750070[203] = 0;
   out_7477745333434750070[204] = 0;
   out_7477745333434750070[205] = 0;
   out_7477745333434750070[206] = 0;
   out_7477745333434750070[207] = 0;
   out_7477745333434750070[208] = 0;
   out_7477745333434750070[209] = 1;
   out_7477745333434750070[210] = 0;
   out_7477745333434750070[211] = 0;
   out_7477745333434750070[212] = 0;
   out_7477745333434750070[213] = 0;
   out_7477745333434750070[214] = 0;
   out_7477745333434750070[215] = 0;
   out_7477745333434750070[216] = 0;
   out_7477745333434750070[217] = 0;
   out_7477745333434750070[218] = 0;
   out_7477745333434750070[219] = 0;
   out_7477745333434750070[220] = 0;
   out_7477745333434750070[221] = 0;
   out_7477745333434750070[222] = 0;
   out_7477745333434750070[223] = 0;
   out_7477745333434750070[224] = 0;
   out_7477745333434750070[225] = 0;
   out_7477745333434750070[226] = 0;
   out_7477745333434750070[227] = 0;
   out_7477745333434750070[228] = 1;
   out_7477745333434750070[229] = 0;
   out_7477745333434750070[230] = 0;
   out_7477745333434750070[231] = 0;
   out_7477745333434750070[232] = 0;
   out_7477745333434750070[233] = 0;
   out_7477745333434750070[234] = 0;
   out_7477745333434750070[235] = 0;
   out_7477745333434750070[236] = 0;
   out_7477745333434750070[237] = 0;
   out_7477745333434750070[238] = 0;
   out_7477745333434750070[239] = 0;
   out_7477745333434750070[240] = 0;
   out_7477745333434750070[241] = 0;
   out_7477745333434750070[242] = 0;
   out_7477745333434750070[243] = 0;
   out_7477745333434750070[244] = 0;
   out_7477745333434750070[245] = 0;
   out_7477745333434750070[246] = 0;
   out_7477745333434750070[247] = 1;
   out_7477745333434750070[248] = 0;
   out_7477745333434750070[249] = 0;
   out_7477745333434750070[250] = 0;
   out_7477745333434750070[251] = 0;
   out_7477745333434750070[252] = 0;
   out_7477745333434750070[253] = 0;
   out_7477745333434750070[254] = 0;
   out_7477745333434750070[255] = 0;
   out_7477745333434750070[256] = 0;
   out_7477745333434750070[257] = 0;
   out_7477745333434750070[258] = 0;
   out_7477745333434750070[259] = 0;
   out_7477745333434750070[260] = 0;
   out_7477745333434750070[261] = 0;
   out_7477745333434750070[262] = 0;
   out_7477745333434750070[263] = 0;
   out_7477745333434750070[264] = 0;
   out_7477745333434750070[265] = 0;
   out_7477745333434750070[266] = 1;
   out_7477745333434750070[267] = 0;
   out_7477745333434750070[268] = 0;
   out_7477745333434750070[269] = 0;
   out_7477745333434750070[270] = 0;
   out_7477745333434750070[271] = 0;
   out_7477745333434750070[272] = 0;
   out_7477745333434750070[273] = 0;
   out_7477745333434750070[274] = 0;
   out_7477745333434750070[275] = 0;
   out_7477745333434750070[276] = 0;
   out_7477745333434750070[277] = 0;
   out_7477745333434750070[278] = 0;
   out_7477745333434750070[279] = 0;
   out_7477745333434750070[280] = 0;
   out_7477745333434750070[281] = 0;
   out_7477745333434750070[282] = 0;
   out_7477745333434750070[283] = 0;
   out_7477745333434750070[284] = 0;
   out_7477745333434750070[285] = 1;
   out_7477745333434750070[286] = 0;
   out_7477745333434750070[287] = 0;
   out_7477745333434750070[288] = 0;
   out_7477745333434750070[289] = 0;
   out_7477745333434750070[290] = 0;
   out_7477745333434750070[291] = 0;
   out_7477745333434750070[292] = 0;
   out_7477745333434750070[293] = 0;
   out_7477745333434750070[294] = 0;
   out_7477745333434750070[295] = 0;
   out_7477745333434750070[296] = 0;
   out_7477745333434750070[297] = 0;
   out_7477745333434750070[298] = 0;
   out_7477745333434750070[299] = 0;
   out_7477745333434750070[300] = 0;
   out_7477745333434750070[301] = 0;
   out_7477745333434750070[302] = 0;
   out_7477745333434750070[303] = 0;
   out_7477745333434750070[304] = 1;
   out_7477745333434750070[305] = 0;
   out_7477745333434750070[306] = 0;
   out_7477745333434750070[307] = 0;
   out_7477745333434750070[308] = 0;
   out_7477745333434750070[309] = 0;
   out_7477745333434750070[310] = 0;
   out_7477745333434750070[311] = 0;
   out_7477745333434750070[312] = 0;
   out_7477745333434750070[313] = 0;
   out_7477745333434750070[314] = 0;
   out_7477745333434750070[315] = 0;
   out_7477745333434750070[316] = 0;
   out_7477745333434750070[317] = 0;
   out_7477745333434750070[318] = 0;
   out_7477745333434750070[319] = 0;
   out_7477745333434750070[320] = 0;
   out_7477745333434750070[321] = 0;
   out_7477745333434750070[322] = 0;
   out_7477745333434750070[323] = 1;
}
void h_4(double *state, double *unused, double *out_3625361759125608085) {
   out_3625361759125608085[0] = state[6] + state[9];
   out_3625361759125608085[1] = state[7] + state[10];
   out_3625361759125608085[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1981232842790120653) {
   out_1981232842790120653[0] = 0;
   out_1981232842790120653[1] = 0;
   out_1981232842790120653[2] = 0;
   out_1981232842790120653[3] = 0;
   out_1981232842790120653[4] = 0;
   out_1981232842790120653[5] = 0;
   out_1981232842790120653[6] = 1;
   out_1981232842790120653[7] = 0;
   out_1981232842790120653[8] = 0;
   out_1981232842790120653[9] = 1;
   out_1981232842790120653[10] = 0;
   out_1981232842790120653[11] = 0;
   out_1981232842790120653[12] = 0;
   out_1981232842790120653[13] = 0;
   out_1981232842790120653[14] = 0;
   out_1981232842790120653[15] = 0;
   out_1981232842790120653[16] = 0;
   out_1981232842790120653[17] = 0;
   out_1981232842790120653[18] = 0;
   out_1981232842790120653[19] = 0;
   out_1981232842790120653[20] = 0;
   out_1981232842790120653[21] = 0;
   out_1981232842790120653[22] = 0;
   out_1981232842790120653[23] = 0;
   out_1981232842790120653[24] = 0;
   out_1981232842790120653[25] = 1;
   out_1981232842790120653[26] = 0;
   out_1981232842790120653[27] = 0;
   out_1981232842790120653[28] = 1;
   out_1981232842790120653[29] = 0;
   out_1981232842790120653[30] = 0;
   out_1981232842790120653[31] = 0;
   out_1981232842790120653[32] = 0;
   out_1981232842790120653[33] = 0;
   out_1981232842790120653[34] = 0;
   out_1981232842790120653[35] = 0;
   out_1981232842790120653[36] = 0;
   out_1981232842790120653[37] = 0;
   out_1981232842790120653[38] = 0;
   out_1981232842790120653[39] = 0;
   out_1981232842790120653[40] = 0;
   out_1981232842790120653[41] = 0;
   out_1981232842790120653[42] = 0;
   out_1981232842790120653[43] = 0;
   out_1981232842790120653[44] = 1;
   out_1981232842790120653[45] = 0;
   out_1981232842790120653[46] = 0;
   out_1981232842790120653[47] = 1;
   out_1981232842790120653[48] = 0;
   out_1981232842790120653[49] = 0;
   out_1981232842790120653[50] = 0;
   out_1981232842790120653[51] = 0;
   out_1981232842790120653[52] = 0;
   out_1981232842790120653[53] = 0;
}
void h_10(double *state, double *unused, double *out_1179392119798824446) {
   out_1179392119798824446[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1179392119798824446[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1179392119798824446[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1288900125489167846) {
   out_1288900125489167846[0] = 0;
   out_1288900125489167846[1] = 9.8100000000000005*cos(state[1]);
   out_1288900125489167846[2] = 0;
   out_1288900125489167846[3] = 0;
   out_1288900125489167846[4] = -state[8];
   out_1288900125489167846[5] = state[7];
   out_1288900125489167846[6] = 0;
   out_1288900125489167846[7] = state[5];
   out_1288900125489167846[8] = -state[4];
   out_1288900125489167846[9] = 0;
   out_1288900125489167846[10] = 0;
   out_1288900125489167846[11] = 0;
   out_1288900125489167846[12] = 1;
   out_1288900125489167846[13] = 0;
   out_1288900125489167846[14] = 0;
   out_1288900125489167846[15] = 1;
   out_1288900125489167846[16] = 0;
   out_1288900125489167846[17] = 0;
   out_1288900125489167846[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1288900125489167846[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1288900125489167846[20] = 0;
   out_1288900125489167846[21] = state[8];
   out_1288900125489167846[22] = 0;
   out_1288900125489167846[23] = -state[6];
   out_1288900125489167846[24] = -state[5];
   out_1288900125489167846[25] = 0;
   out_1288900125489167846[26] = state[3];
   out_1288900125489167846[27] = 0;
   out_1288900125489167846[28] = 0;
   out_1288900125489167846[29] = 0;
   out_1288900125489167846[30] = 0;
   out_1288900125489167846[31] = 1;
   out_1288900125489167846[32] = 0;
   out_1288900125489167846[33] = 0;
   out_1288900125489167846[34] = 1;
   out_1288900125489167846[35] = 0;
   out_1288900125489167846[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1288900125489167846[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1288900125489167846[38] = 0;
   out_1288900125489167846[39] = -state[7];
   out_1288900125489167846[40] = state[6];
   out_1288900125489167846[41] = 0;
   out_1288900125489167846[42] = state[4];
   out_1288900125489167846[43] = -state[3];
   out_1288900125489167846[44] = 0;
   out_1288900125489167846[45] = 0;
   out_1288900125489167846[46] = 0;
   out_1288900125489167846[47] = 0;
   out_1288900125489167846[48] = 0;
   out_1288900125489167846[49] = 0;
   out_1288900125489167846[50] = 1;
   out_1288900125489167846[51] = 0;
   out_1288900125489167846[52] = 0;
   out_1288900125489167846[53] = 1;
}
void h_13(double *state, double *unused, double *out_5336829018404406652) {
   out_5336829018404406652[0] = state[3];
   out_5336829018404406652[1] = state[4];
   out_5336829018404406652[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5193506668122453454) {
   out_5193506668122453454[0] = 0;
   out_5193506668122453454[1] = 0;
   out_5193506668122453454[2] = 0;
   out_5193506668122453454[3] = 1;
   out_5193506668122453454[4] = 0;
   out_5193506668122453454[5] = 0;
   out_5193506668122453454[6] = 0;
   out_5193506668122453454[7] = 0;
   out_5193506668122453454[8] = 0;
   out_5193506668122453454[9] = 0;
   out_5193506668122453454[10] = 0;
   out_5193506668122453454[11] = 0;
   out_5193506668122453454[12] = 0;
   out_5193506668122453454[13] = 0;
   out_5193506668122453454[14] = 0;
   out_5193506668122453454[15] = 0;
   out_5193506668122453454[16] = 0;
   out_5193506668122453454[17] = 0;
   out_5193506668122453454[18] = 0;
   out_5193506668122453454[19] = 0;
   out_5193506668122453454[20] = 0;
   out_5193506668122453454[21] = 0;
   out_5193506668122453454[22] = 1;
   out_5193506668122453454[23] = 0;
   out_5193506668122453454[24] = 0;
   out_5193506668122453454[25] = 0;
   out_5193506668122453454[26] = 0;
   out_5193506668122453454[27] = 0;
   out_5193506668122453454[28] = 0;
   out_5193506668122453454[29] = 0;
   out_5193506668122453454[30] = 0;
   out_5193506668122453454[31] = 0;
   out_5193506668122453454[32] = 0;
   out_5193506668122453454[33] = 0;
   out_5193506668122453454[34] = 0;
   out_5193506668122453454[35] = 0;
   out_5193506668122453454[36] = 0;
   out_5193506668122453454[37] = 0;
   out_5193506668122453454[38] = 0;
   out_5193506668122453454[39] = 0;
   out_5193506668122453454[40] = 0;
   out_5193506668122453454[41] = 1;
   out_5193506668122453454[42] = 0;
   out_5193506668122453454[43] = 0;
   out_5193506668122453454[44] = 0;
   out_5193506668122453454[45] = 0;
   out_5193506668122453454[46] = 0;
   out_5193506668122453454[47] = 0;
   out_5193506668122453454[48] = 0;
   out_5193506668122453454[49] = 0;
   out_5193506668122453454[50] = 0;
   out_5193506668122453454[51] = 0;
   out_5193506668122453454[52] = 0;
   out_5193506668122453454[53] = 0;
}
void h_14(double *state, double *unused, double *out_2890500241112110034) {
   out_2890500241112110034[0] = state[6];
   out_2890500241112110034[1] = state[7];
   out_2890500241112110034[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5944473699129605182) {
   out_5944473699129605182[0] = 0;
   out_5944473699129605182[1] = 0;
   out_5944473699129605182[2] = 0;
   out_5944473699129605182[3] = 0;
   out_5944473699129605182[4] = 0;
   out_5944473699129605182[5] = 0;
   out_5944473699129605182[6] = 1;
   out_5944473699129605182[7] = 0;
   out_5944473699129605182[8] = 0;
   out_5944473699129605182[9] = 0;
   out_5944473699129605182[10] = 0;
   out_5944473699129605182[11] = 0;
   out_5944473699129605182[12] = 0;
   out_5944473699129605182[13] = 0;
   out_5944473699129605182[14] = 0;
   out_5944473699129605182[15] = 0;
   out_5944473699129605182[16] = 0;
   out_5944473699129605182[17] = 0;
   out_5944473699129605182[18] = 0;
   out_5944473699129605182[19] = 0;
   out_5944473699129605182[20] = 0;
   out_5944473699129605182[21] = 0;
   out_5944473699129605182[22] = 0;
   out_5944473699129605182[23] = 0;
   out_5944473699129605182[24] = 0;
   out_5944473699129605182[25] = 1;
   out_5944473699129605182[26] = 0;
   out_5944473699129605182[27] = 0;
   out_5944473699129605182[28] = 0;
   out_5944473699129605182[29] = 0;
   out_5944473699129605182[30] = 0;
   out_5944473699129605182[31] = 0;
   out_5944473699129605182[32] = 0;
   out_5944473699129605182[33] = 0;
   out_5944473699129605182[34] = 0;
   out_5944473699129605182[35] = 0;
   out_5944473699129605182[36] = 0;
   out_5944473699129605182[37] = 0;
   out_5944473699129605182[38] = 0;
   out_5944473699129605182[39] = 0;
   out_5944473699129605182[40] = 0;
   out_5944473699129605182[41] = 0;
   out_5944473699129605182[42] = 0;
   out_5944473699129605182[43] = 0;
   out_5944473699129605182[44] = 1;
   out_5944473699129605182[45] = 0;
   out_5944473699129605182[46] = 0;
   out_5944473699129605182[47] = 0;
   out_5944473699129605182[48] = 0;
   out_5944473699129605182[49] = 0;
   out_5944473699129605182[50] = 0;
   out_5944473699129605182[51] = 0;
   out_5944473699129605182[52] = 0;
   out_5944473699129605182[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7224170274929451769) {
  err_fun(nom_x, delta_x, out_7224170274929451769);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_580510085257942810) {
  inv_err_fun(nom_x, true_x, out_580510085257942810);
}
void pose_H_mod_fun(double *state, double *out_7521149564861609621) {
  H_mod_fun(state, out_7521149564861609621);
}
void pose_f_fun(double *state, double dt, double *out_5784399927549256008) {
  f_fun(state,  dt, out_5784399927549256008);
}
void pose_F_fun(double *state, double dt, double *out_7477745333434750070) {
  F_fun(state,  dt, out_7477745333434750070);
}
void pose_h_4(double *state, double *unused, double *out_3625361759125608085) {
  h_4(state, unused, out_3625361759125608085);
}
void pose_H_4(double *state, double *unused, double *out_1981232842790120653) {
  H_4(state, unused, out_1981232842790120653);
}
void pose_h_10(double *state, double *unused, double *out_1179392119798824446) {
  h_10(state, unused, out_1179392119798824446);
}
void pose_H_10(double *state, double *unused, double *out_1288900125489167846) {
  H_10(state, unused, out_1288900125489167846);
}
void pose_h_13(double *state, double *unused, double *out_5336829018404406652) {
  h_13(state, unused, out_5336829018404406652);
}
void pose_H_13(double *state, double *unused, double *out_5193506668122453454) {
  H_13(state, unused, out_5193506668122453454);
}
void pose_h_14(double *state, double *unused, double *out_2890500241112110034) {
  h_14(state, unused, out_2890500241112110034);
}
void pose_H_14(double *state, double *unused, double *out_5944473699129605182) {
  H_14(state, unused, out_5944473699129605182);
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
