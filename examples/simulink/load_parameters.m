close all 
clc

dim = hpipm_ocp_qp_dim('qp_data.c');

% extract dims
N = dim.get('N');
NU = dim.get('nu', 0);
NX = dim.get('nx', 0);

x0 = [-1 3];
Ts = 0.1;

