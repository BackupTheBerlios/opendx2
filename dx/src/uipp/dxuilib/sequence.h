"macro main(",
") -> (",
") {",
"main_GetLocal_1_o1,",
"main_GetLocal_1_o2 = ",
"GetLocal(",
"main_GetLocal_1_i1,",
"main_GetLocal_1_i2,",
"main_GetLocal_1_i3",
") [instance: 1, cache: 1];",
"main_Compute2_1_o1 = ",
"Compute2(",
"main_Compute2_1_i1,",
"main_Compute2_1_i2,",
"main_GetLocal_1_o1,",
"main_Compute2_1_i4,",
"main_Compute2_1_i5",
") [instance: 1, cache: 1];",
"main_GetGlobal_1_o1,",
"main_GetGlobal_1_o2 = ",
"GetGlobal(",
"main_GetGlobal_1_i1,",
"main_GetGlobal_1_i2,",
"main_GetGlobal_1_i3",
") [instance: 1, cache: 1];",
"main_Compute2_2_o1 = ",
"Compute2(",
"main_Compute2_2_i1,",
"main_Compute2_2_i2,",
"main_GetGlobal_1_o1,",
"main_Compute2_2_i4,",
"main_Compute2_2_i5",
") [instance: 2, cache: 1];",
"main_Compute2_3_o1 = ",
"Compute2(",
"main_Compute2_3_i1,",
"main_Compute2_3_i2,",
"main_Compute2_1_o1,",
"main_Compute2_3_i4,",
"main_Compute2_2_o1",
") [instance: 3, cache: 1];",
"main_Compute_1_o1 = ",
"Compute(",
"main_Compute_1_i1,",
"main_Compute2_3_o1,",
"main_GetLocal_1_o1",
") [instance: 1, cache: 1];",
"main_DXLInp1_o1 = _java_control;",
"SetGlobal(",
"main_Compute2_2_o1,",
"main_GetGlobal_1_o2,",
"main_SetGlobal_1_i3",
") [instance: 1, cache: 1];",
"SetLocal(",
"main_Compute2_1_o1,",
"main_GetLocal_1_o2,",
"main_SetLocal_1_i3",
") [instance: 1, cache: 1];",
"java_sequence = main_Compute_1_o1;",
"java_control = main_DXLInp1_o1;",
"}",
"main_GetLocal_1_i1 = 0;",
"main_Compute2_1_i1 = \"loop+1\";",
"main_Compute2_1_i2 = \"loop\";",
"main_GetGlobal_1_i1 = 0;",
"main_Compute2_2_i1 = \"loop+1\";",
"main_Compute2_2_i2 = \"loop\";",
"main_Compute2_3_i1 = \"global-local\";",
"main_Compute2_3_i2 = \"local\";",
"main_Compute2_3_i4 = \"global\";",
"main_Compute_1_i1 = \"[$0, $1]\";",
"_java_control = 0;",
"Executive(\"product version 4 2 0\");",
"$sync",
NULL
