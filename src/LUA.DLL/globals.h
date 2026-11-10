/* LUA.DLL: every global / string symbol referenced by the decompiled code.
 * Named globals carry their Ghidra type. For DAT_/PTR_/s_ symbols Ghidra exported
 * no type; the type below is inferred from how the code uses the symbol
 * (see infer_global_types in tools/build_src.py) - fix it in Ghidra, not here. */
#pragma once
#include "ghidra_types.h"

/* ---- named globals (type from Ghidra) ---- */
extern code *lua_callhook; /* 0x1002bec8, undefined4 in Ghidra */
extern code *lua_linehook; /* 0x1002becc, undefined4 in Ghidra */
extern code *lua_taskhook; /* 0x1002bed0, undefined4 in Ghidra */
extern code *lua_savehook; /* 0x1002bed4, undefined4 in Ghidra */
extern code *lua_restorehook; /* 0x1002bed8, undefined4 in Ghidra */
extern undefined4 lua_assume_binary; /* 0x1002bee0, undefined4 in Ghidra */
extern undefined4 lua_debug; /* 0x1002bee4, undefined4 in Ghidra */

/* ---- unnamed data (type inferred from use) ---- */
extern code LAB_1000f3b0;  /* code label (address only) */ /* used by 2 fn(s), first 0x1000f3d2 */
extern code LAB_1001dec8;  /* code label (address only) */ /* used by 6 fn(s), first 0x10013930 */
extern undefined g_aYytranslate; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYyr1; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYyr2; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined2 g_wYydefact; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYydefgoto; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined2 g_wYypact; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYypgoto; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYytable; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined g_aYycheck; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined DAT_10023c40; /* used by 1 fn(s), first 0x1000ffd0 */
extern undefined DAT_10023d78; /* used by 1 fn(s), first 0x10010c20 */
extern undefined DAT_10023dc4; /* used by 1 fn(s), first 0x10011290 */
extern undefined DAT_10023dc8; /* used by 1 fn(s), first 0x10011290 */
extern undefined DAT_10023dd0; /* used by 1 fn(s), first 0x10011a40 */
extern undefined DAT_10023e28; /* used by 1 fn(s), first 0x10013930 */
extern undefined DAT_10023e38; /* used by 1 fn(s), first 0x10013aa0 */
extern undefined DAT_10023e50; /* used by 1 fn(s), first 0x10013c30 */
extern undefined DAT_10023e60; /* used by 1 fn(s), first 0x10013e40 */
extern undefined DAT_10023e70; /* used by 1 fn(s), first 0x10014120 */
extern undefined *PTR_FUN_10023e80; /* used by 1 fn(s), first 0x10014370 */
extern undefined DAT_10023e88; /* used by 1 fn(s), first 0x100141b0 */
extern undefined DAT_10023ea0; /* used by 1 fn(s), first 0x10014370 */
extern undefined DAT_1002425c; /* used by 1 fn(s), first 0x10015940 */
extern undefined DAT_100242c8; /* used by 1 fn(s), first 0x10016230 */
extern undefined DAT_1002494c; /* used by 1 fn(s), first 0x10018400 */
extern undefined DAT_10024950; /* used by 1 fn(s), first 0x10018400 */
extern undefined4 DAT_10024d10; /* used by 1 fn(s), first 0x1001d340 */
extern undefined DAT_10024d2c; /* used by 1 fn(s), first 0x1001d340 */
extern undefined4 DAT_10024d30; /* used by 1 fn(s), first 0x1001d340 */
extern undefined UNK_10024df8; /* used by 1 fn(s), first 0x10021fbb */
extern undefined UNK_10024e78; /* used by 1 fn(s), first 0x1002201b */
extern undefined DAT_10026000; /* used by 1 fn(s), first 0x10015590 */
extern undefined DAT_10026004; /* used by 1 fn(s), first 0x10015590 */
extern undefined DAT_10026008; /* used by 1 fn(s), first 0x10015590 */
extern undefined DAT_10026014; /* used by 1 fn(s), first 0x10015590 */
extern undefined DAT_10026018; /* used by 1 fn(s), first 0x100155f0 */
extern undefined DAT_10026024; /* used by 1 fn(s), first 0x100155f0 */
extern undefined DAT_10026028; /* used by 1 fn(s), first 0x100155f0 */
extern undefined DAT_10026030; /* used by 1 fn(s), first 0x100155f0 */
extern char s_aEntries____numEntries___0_100260b8[]; /* used by 2 fn(s), first 0x10001000 */
extern char s_C__grimsrc_libs_lua_src_lapi_cpp_100260d4[]; /* used by 4 fn(s), first 0x10001000 */
extern char s_API_error___wrong_number_of_argu_100260f8[]; /* used by 1 fn(s), first 0x100012b0 */
extern char s_indexed_expression_not_a_table_i_10026130[]; /* used by 1 fn(s), first 0x10001540 */
extern char s_API_error___attempt_to_push_a_NU_10026160[]; /* used by 1 fn(s), first 0x10001b10 */
extern char s_API_error___attempt_to_push_a_NO_10026190[]; /* used by 1 fn(s), first 0x10001c40 */
extern char s_cannot_change_the_tag_of_a___20s_100261b8[]; /* used by 1 fn(s), first 0x10001d30 */
extern char s_L__pExecutionState_100261dc[]; /* used by 1 fn(s), first 0x10001e10 */
extern undefined DAT_100261f0; /* used by 2 fn(s), first 0x100020f0 */
extern char s__in_file__s__100261f4[]; /* used by 1 fn(s), first 0x100020f0 */
extern char s_at_line__d_10026204[]; /* used by 1 fn(s), first 0x100020f0 */
extern char s_function__s_10026210[]; /* used by 1 fn(s), first 0x100020f0 */
extern char s___s__tag_method_1002621c[]; /* used by 1 fn(s), first 0x100020f0 */
extern char s_function___s__d__1002622c[]; /* used by 1 fn(s), first 0x100020f0 */
extern undefined DAT_10026240; /* used by 1 fn(s), first 0x100020f0 */
extern char s_main_of__s_10026244[]; /* used by 1 fn(s), first 0x100020f0 */
extern undefined DAT_10026250; /* used by 1 fn(s), first 0x100020f0 */
extern char s_Active_Stack__10026254[]; /* used by 1 fn(s), first 0x100020f0 */
extern undefined DAT_10026264; /* used by 2 fn(s), first 0x100023c0 */
extern char s_API____funcinfo__called_with_a_n_10026268[]; /* used by 1 fn(s), first 0x100023c0 */
extern char s_global_1002629c[]; /* used by 1 fn(s), first 0x10002440 */
extern char s_tag_method_100262a4[]; /* used by 1 fn(s), first 0x10002440 */
extern char s_too_many_nested_blocks_100262b0[]; /* used by 1 fn(s), first 0x100024c0 */
extern char s_pNewState__Restore_restoreFunc____100262c8[]; /* used by 1 fn(s), first 0x10002760 */
extern char s_numTasks___0_100262f4[]; /* used by 1 fn(s), first 0x10002760 */
extern char s_bad_argument___d_to_function_____10026304[]; /* used by 1 fn(s), first 0x100029d0 */
extern char s_bad_argument___d_to_function_____10026334[]; /* used by 1 fn(s), first 0x100029d0 */
extern undefined DAT_1002635c; /* used by 1 fn(s), first 0x100029d0 */
extern char s_C__grimsrc_libs_lua_src_lbuffer__100263b4[]; /* used by 1 fn(s), first 0x10002c50 */
extern undefined *g_pInt_funcs; /* used by 1 fn(s), first 0x10003df0 */
extern char s_error_10026648[]; /* used by 1 fn(s), first 0x1000cb80 */
extern char s_invalid_2nd_argument__probably_o_100266b8[]; /* used by 1 fn(s), first 0x100030d0 */
extern char s_internal_error_100266e8[]; /* used by 1 fn(s), first 0x10003170 */
extern undefined DAT_100266f8; /* used by 1 fn(s), first 0x10003170 */
extern char s_task___d_100266fc[]; /* used by 1 fn(s), first 0x10003170 */
extern char s_userdata___p_10026708[]; /* used by 1 fn(s), first 0x10003170 */
extern char s_function___p_10026718[]; /* used by 1 fn(s), first 0x10003170 */
extern char s_table___p_10026728[]; /* used by 1 fn(s), first 0x10003170 */
extern char s_Current_task_is_committing_suici_10026734[]; /* used by 1 fn(s), first 0x10003370 */
extern char s_Argument_to_stopscript_must_be_a_1002675c[]; /* used by 1 fn(s), first 0x10003370 */
extern char s_Too_few_arguments_to_stopscript__10026798[]; /* used by 1 fn(s), first 0x10003370 */
extern char s_Argument_to_findscript_must_be_a_100267ec[]; /* used by 1 fn(s), first 0x100034c0 */
extern char s_Too_few_arguments_to_findscript__10026828[]; /* used by 1 fn(s), first 0x100034c0 */
extern char s_Argument_to_identifyscript_must_b_10026870[]; /* used by 1 fn(s), first 0x10003610 */
extern char s_Too_few_arguments_to_identifyscr_100268a4[]; /* used by 1 fn(s), first 0x10003610 */
extern char s_Argument_to_nextscript_must_be_n_100268e8[]; /* used by 1 fn(s), first 0x100036a0 */
extern char s_Too_few_arguments_to_nextscript__10026920[]; /* used by 1 fn(s), first 0x100036a0 */
extern undefined DAT_10026960; /* used by 1 fn(s), first 0x10003780 */
extern char s_assertion_failed____100s_10026978[]; /* used by 1 fn(s), first 0x10003930 */
extern undefined DAT_10026994; /* used by 2 fn(s), first 0x10003ba0 */
extern char s__VERSION_10026998[]; /* used by 1 fn(s), first 0x10003df0 */
extern char s_Lua_3_1__alpha__100269a4[]; /* used by 1 fn(s), first 0x10003df0 */
extern char s_not_enough_memory_100269b4[]; /* used by 2 fn(s), first 0x10003df0 */
extern char s_table_overflow_100269c8[]; /* used by 2 fn(s), first 0x10003df0 */
extern char s_stack_size_overflow_100269d8[]; /* used by 1 fn(s), first 0x10003e40 */
extern char s_Lua2C___C2Lua_overflow_100269ec[]; /* used by 1 fn(s), first 0x10003e40 */
extern char s_C__grimsrc_libs_lua_src_ldo_cpp_10026a04[]; /* used by 2 fn(s), first 0x10003e40 */
extern char s__return__10026a24[]; /* used by 1 fn(s), first 0x10004000 */
extern char s_call_expression_not_a_function_10026a30[]; /* used by 1 fn(s), first 0x10004180 */
extern char s_unexpected_cmark_at__d_10026a50[]; /* used by 1 fn(s), first 0x10004180 */
extern char s_lua__Unable_to_recover__10026a68[]; /* used by 1 fn(s), first 0x10004650 */
extern undefined DAT_10026a80; /* used by 2 fn(s), first 0x10004890 */
extern char s__stdin__10026a84[]; /* used by 1 fn(s), first 0x10004890 */
extern undefined DAT_10026a8c; /* used by 1 fn(s), first 0x10004890 */
extern char s__dostring_______20s_10026a90[]; /* used by 1 fn(s), first 0x10004b20 */
extern char s_C__grimsrc_libs_lua_src_lfunc_cp_10026aa4[]; /* used by 2 fn(s), first 0x10004ba0 */
extern char s_reference_table_overflow_10026ac8[]; /* used by 1 fn(s), first 0x10004d40 */
extern undefined g_aSetloc_cat; /* used by 1 fn(s), first 0x100059c0 */
extern undefined *g_pIolib; /* used by 1 fn(s), first 0x10005ae0 */
extern undefined *PTR_s_readfrom_10026b50; /* used by 1 fn(s), first 0x10005b20 */
extern char s_write_10026b78[]; /* used by 1 fn(s), first 0x10005b20 */
extern char s__INPUT_10026c00[]; /* used by 3 fn(s), first 0x10005320 */
extern char s_global_variable____50s__is_not_a_10026c08[]; /* used by 1 fn(s), first 0x10005480 */
extern char s_cannot_access_a_closed_file_10026c38[]; /* used by 1 fn(s), first 0x100054c0 */
extern undefined DAT_10026c54; /* used by 1 fn(s), first 0x10005570 */
extern char s__OUTPUT_10026c58[]; /* used by 4 fn(s), first 0x10005570 */
extern undefined DAT_10026c60; /* used by 1 fn(s), first 0x10005620 */
extern char s_unbalanced_braces_in_read_patter_10026c64[]; /* used by 1 fn(s), first 0x10005660 */
extern char s__________10026c88[]; /* used by 1 fn(s), first 0x10005660 */
extern char s_invalid__date__format_10026c94[]; /* used by 1 fn(s), first 0x10005940 */
extern undefined DAT_10026cac; /* used by 1 fn(s), first 0x10005940 */
extern char s_FALSE_10026cc0[]; /* used by 1 fn(s), first 0x10005a20 */
extern char s_C__grimsrc_libs_lua_src_liolib_c_10026cc8[]; /* used by 1 fn(s), first 0x10005a20 */
extern undefined DAT_10026cec; /* used by 1 fn(s), first 0x10005a50 */
extern char s__STDERR_10026cf4[]; /* used by 1 fn(s), first 0x10005b20 */
extern char s__STDOUT_10026cfc[]; /* used by 1 fn(s), first 0x10005b20 */
extern char s__STDIN_10026d04[]; /* used by 1 fn(s), first 0x10005b20 */
extern undefined4 DAT_10026d14; /* used by 1 fn(s), first 0x10005c00 */
extern undefined *PTR_DAT_10026d90; /* used by 1 fn(s), first 0x10006b60 */
extern undefined *PTR_DAT_10026d94; /* used by 1 fn(s), first 0x10005c00 */
extern undefined *g_pInclinenumber_pragmas; /* used by 1 fn(s), first 0x10006890 */
extern char s_input_ends_inside_a__if_10026e44[]; /* used by 2 fn(s), first 0x10005d00 */
extern char s_ambiguous_syntax__decimal_point_x_10026e5c[]; /* used by 1 fn(s), first 0x10005d00 */
extern char s_invalid_pragma_format_10026e94[]; /* used by 1 fn(s), first 0x10006890 */
extern char s_unknown_pragma_10026eac[]; /* used by 1 fn(s), first 0x10006890 */
extern char s_unmatched__else_10026ebc[]; /* used by 1 fn(s), first 0x10006890 */
extern char s__else_10026ecc[]; /* used by 1 fn(s), first 0x10006890 */
extern char s_too_many_nested__ifs_10026ed4[]; /* used by 1 fn(s), first 0x10006890 */
extern undefined DAT_10026eec; /* used by 1 fn(s), first 0x10006890 */
extern char s_unmatched__end_10026ef0[]; /* used by 1 fn(s), first 0x10006890 */
extern undefined DAT_10026f00; /* used by 1 fn(s), first 0x10006890 */
extern char s_invalid__if_condition_10026f08[]; /* used by 1 fn(s), first 0x10006b60 */
extern char s_pragma_too_long_10026f20[]; /* used by 1 fn(s), first 0x10006bb0 */
extern undefined *g_pMathlib; /* used by 1 fn(s), first 0x10007320 */
extern undefined DAT_10027004; /* used by 1 fn(s), first 0x10007320 */
extern undefined DAT_1002706c; /* used by 1 fn(s), first 0x10007320 */
extern undefined DAT_10027070; /* used by 1 fn(s), first 0x10007320 */
extern char s__TRIGMODE_10027074[]; /* used by 1 fn(s), first 0x10007320 */
extern char s_C__grimsrc_libs_lua_src_lmem_cpp_10027080[]; /* used by 2 fn(s), first 0x100073b0 */
extern undefined *g_pLuaO_typenames; /* used by 2 fn(s), first 0x10001d30 */
extern undefined g_LuaO_nilobject; /* used by 4 fn(s), first 0x10004e30 */
extern int g_dwDimensions; /* used by 1 fn(s), first 0x10007450 */
extern char s_internal_error_in__lua_equalObj__10027180[]; /* used by 1 fn(s), first 0x100074b0 */
extern undefined DAT_100271ac; /* used by 1 fn(s), first 0x100085e0 */
extern char s_C__grimsrc_libs_lua_src_lstate_c_100277cc[]; /* used by 6 fn(s), first 0x100075e0 */
extern char s_aStringPtrs____aClosurePtrs____a_100277f0[]; /* used by 1 fn(s), first 0x10007660 */
extern char s_pTString_10027828[]; /* used by 1 fn(s), first 0x100079d0 */
extern char s_op____sizeof_opcodeDirectory__si_10027834[]; /* used by 1 fn(s), first 0x100085e0 */
extern char s_pExecutionState_____pPreviousSta_10027870[]; /* used by 1 fn(s), first 0x10008640 */
extern undefined g_EMPTY; /* used by 8 fn(s), first 0x10008dc0 */
extern char s_C__grimsrc_libs_lua_src_lstring__100278b4[]; /* used by 3 fn(s), first 0x10008d40 */
extern undefined *g_pStrlib; /* used by 1 fn(s), first 0x1000a6e0 */
extern char s_incorrect_pattern__missing______10027980[]; /* used by 1 fn(s), first 0x100097f0 */
extern char s_incorrect_pattern__ends_with___c_100279a0[]; /* used by 1 fn(s), first 0x100097f0 */
extern char s___________100279c4[]; /* used by 1 fn(s), first 0x10009cb0 */
extern char s_unfinished_capture_100279d0[]; /* used by 1 fn(s), first 0x10009e40 */
extern char s_too_many_captures_100279e4[]; /* used by 1 fn(s), first 0x10009ea0 */
extern char s_invalid_pattern_capture_100279f8[]; /* used by 1 fn(s), first 0x1000a030 */
extern char s_unbalanced_pattern_10027a10[]; /* used by 1 fn(s), first 0x1000a060 */
extern char s_invalid_capture_index_10027a24[]; /* used by 1 fn(s), first 0x1000a150 */
extern char s_invalid_option_in__format__10027a58[]; /* used by 1 fn(s), first 0x1000a440 */
extern char s_invalid_format__width_or_precisi_10027a74[]; /* used by 1 fn(s), first 0x1000a440 */
extern char s__d_____________d_______d___10027aa4[]; /* used by 1 fn(s), first 0x1000a440 */
extern undefined DAT_10027ac0; /* used by 1 fn(s), first 0x1000a680 */
extern char s___100s__last_token_read_____50s__10027ac4[]; /* used by 1 fn(s), first 0x1000a6f0 */
extern char s__eof__10027b00[]; /* used by 1 fn(s), first 0x1000a6f0 */
extern char s_code_size_overflow_10027b08[]; /* used by 1 fn(s), first 0x1000a7d0 */
extern char s_code_too_long__limit_64K__10027b1c[]; /* used by 1 fn(s), first 0x1000a810 */
extern char s_function_expression_too_complex_10027b38[]; /* used by 1 fn(s), first 0x1000a8b0 */
extern char s_parse_error_10027b58[]; /* used by 2 fn(s), first 0x1000a900 */
extern char s_lua_stx_10027b64[]; /* used by 1 fn(s), first 0x1000aa40 */
extern char s_parser_stack_overflow_10027b6c[]; /* used by 1 fn(s), first 0x1000abd0 */
extern char s_invalid_constructor_syntax_10027b84[]; /* used by 1 fn(s), first 0x1000abd0 */
extern undefined DAT_10027ba0; /* used by 1 fn(s), first 0x1000abd0 */
extern char s_constant_table_overflow_10027ba8[]; /* used by 1 fn(s), first 0x1000b860 */
extern char s_too_many_local_variables__limit__10027bc0[]; /* used by 1 fn(s), first 0x1000ba20 */
extern char s_variable_buffer_overflow__limit__10027be4[]; /* used by 1 fn(s), first 0x1000ba90 */
extern char s_cannot_access_a_variable_in_oute_10027c08[]; /* used by 1 fn(s), first 0x1000baf0 */
extern char s_cannot_access_an_upvalue_in_curr_10027c30[]; /* used by 1 fn(s), first 0x1000bbd0 */
extern char s_cannot_access_upvalue_in_main_10027c5c[]; /* used by 1 fn(s), first 0x1000bbd0 */
extern char s_too_many_upvalues_in_a_single_fu_10027c7c[]; /* used by 1 fn(s), first 0x1000bc40 */
extern undefined DAT_10027cb0; /* used by 1 fn(s), first 0x1000bde0 */
extern char s_too_many_nested_functions__limit_10027cb4[]; /* used by 1 fn(s), first 0x1000c100 */
extern char s_writtenItems____numItems_10027cd8[]; /* used by 1 fn(s), first 0x1000c200 */
extern char s_C__grimsrc_libs_lua_src_ltable_c_10027cf4[]; /* used by 4 fn(s), first 0x1000c200 */
extern char s_unexpected_type_to_index_table_10027d18[]; /* used by 1 fn(s), first 0x1000c580 */
extern undefined *g_pLuaT_eventname; /* used by 5 fn(s), first 0x1000ca60 */
extern undefined DAT_10027db0; /* used by 1 fn(s), first 0x1000c9c0 */
extern undefined *g_pLuaT_setfallback_oldnames; /* used by 1 fn(s), first 0x1000cc30 */
extern char s_C__grimsrc_libs_lua_src_ltm_cpp_10027ed4[]; /* used by 1 fn(s), first 0x1000c850 */
extern char s_tag__d_is_not_result_of__newtag__10027ef4[]; /* used by 1 fn(s), first 0x1000c920 */
extern char s__d_is_not_a_valid_tag_10027f18[]; /* used by 1 fn(s), first 0x1000c9f0 */
extern char s____50s__is_not_a_valid_event_nam_10027f30[]; /* used by 1 fn(s), first 0x1000cab0 */
extern char s_settagmethod__cannot_change_inte_10027f54[]; /* used by 1 fn(s), first 0x1000cae0 */
extern char s_unexpected_type_10027f94[]; /* used by 1 fn(s), first 0x1000cc20 */
extern char s____50s__is_not_a_valid_fallback_n_10027fa4[]; /* used by 1 fn(s), first 0x1000cc30 */
extern char s__s_is_not_a_lua_binary_file_10027fcc[]; /* used by 1 fn(s), first 0x1000cea0 */
extern char s_unexpected_end_of_binary_file__s_10027fe8[]; /* used by 1 fn(s), first 0x1000d010 */
extern char s_C__grimsrc_libs_lua_src_lundump__1002800c[]; /* used by 3 fn(s), first 0x1000d030 */
extern char s_code_too_long___ld_bytes__10028030[]; /* used by 1 fn(s), first 0x1000d090 */
extern char s_floats_in_binary_file__s_have__d_1002804c[]; /* used by 1 fn(s), first 0x1000d420 */
extern char s_unknown_float_representation_in_b_10028098[]; /* used by 1 fn(s), first 0x1000d420 */
extern char s_binary_file__s_too_old__version__100280c8[]; /* used by 1 fn(s), first 0x1000d420 */
extern char s_binary_file__s_too_new__version__1002810c[]; /* used by 1 fn(s), first 0x1000d420 */
extern char s_bad_signature_in_binary_file__s_1002814c[]; /* used by 1 fn(s), first 0x1000d570 */
extern char DAT_1002816c; /* used by 1 fn(s), first 0x1000d570 */
extern char s__lf__c_10028170[]; /* used by 1 fn(s), first 0x1000d5c0 */
extern undefined DAT_10028178; /* used by 1 fn(s), first 0x1000d620 */
extern undefined DAT_1002817c; /* used by 1 fn(s), first 0x1000d620 */
extern char s_indexed_expression_not_a_table_10028180[]; /* used by 2 fn(s), first 0x1000d740 */
extern char s_unexpected_type_for_concatenatio_100281a0[]; /* used by 1 fn(s), first 0x1000df40 */
extern char s_WARNING__Killing_Lua_script_that_100281c4[]; /* used by 1 fn(s), first 0x1000df40 */
extern char s_WARNING__Lua_nesting_level_now___1002821c[]; /* used by 1 fn(s), first 0x1000df40 */
extern char s_unexpected_type_in_arithmetic_op_1002825c[]; /* used by 1 fn(s), first 0x1000ecf0 */
extern char s_unexpected_type_in_comparison_10028284[]; /* used by 1 fn(s), first 0x1000ed10 */
extern undefined *PTR_lzio__ef20_100282ac; /* used by 1 fn(s), first 0x10015590 */
extern undefined4 DAT_100282bc; /* used by 2 fn(s), first 0x1000f45d */
extern undefined4 DAT_100282c0; /* used by 2 fn(s), first 0x1000f45d */
extern int DAT_100282c4; /* used by 2 fn(s), first 0x1000f45d */
extern undefined *PTR_DAT_100282d0; /* used by 6 fn(s), first 0x10004890 */
extern undefined DAT_100282f0; /* used by 6 fn(s), first 0x10005430 */
extern undefined DAT_10028310; /* used by 3 fn(s), first 0x10005b20 */
extern undefined4 DAT_10028550; /* used by 1 fn(s), first 0x1000ff30 */
extern undefined *PTR_DAT_100286b8; /* used by 2 fn(s), first 0x1000ff30 */
extern undefined *PTR_PTR_10028764; /* used by 2 fn(s), first 0x100103f0 */
extern undefined DAT_10028768; /* used by 1 fn(s), first 0x10011560 */
extern char * DAT_10028774; /* used by 3 fn(s), first 0x10011290 */
extern undefined DAT_10028778; /* used by 1 fn(s), first 0x10011560 */
extern undefined *PTR_DAT_1002877c; /* used by 1 fn(s), first 0x10011290 */
extern undefined *PTR_DAT_10028780; /* used by 1 fn(s), first 0x100116c0 */
extern undefined *PTR_DAT_1002878c; /* used by 1 fn(s), first 0x100116c0 */
extern undefined DAT_100287b8; /* used by 1 fn(s), first 0x100117e0 */
extern undefined DAT_10028840; /* used by 1 fn(s), first 0x100117e0 */
extern undefined DAT_100288d0; /* used by 1 fn(s), first 0x10011d6d */
extern undefined DAT_100288e0; /* used by 1 fn(s), first 0x10011e3d */
extern undefined DAT_10028940; /* used by 1 fn(s), first 0x10012325 */
extern undefined *PTR_DAT_10028950; /* used by 23 fn(s), first 0x10009a10 */
extern undefined *PTR_DAT_10028954; /* used by 2 fn(s), first 0x100178e0 */
extern undefined DAT_1002895a; /* used by 1 fn(s), first 0x100178e0 */
extern undefined4 DAT_10028b5c; /* used by 21 fn(s), first 0x10009a10 */
extern undefined DAT_10028b60; /* used by 7 fn(s), first 0x10012f60 */
extern undefined DAT_10028b64; /* used by 1 fn(s), first 0x100173f0 */
extern undefined *PTR_exit_10028b70; /* used by 1 fn(s), first 0x10012e80 */
extern undefined *PTR_FUN_10028b78; /* used by 2 fn(s), first 0x1000ef40 */
extern undefined *PTR_FUN_10028b7c; /* used by 2 fn(s), first 0x1000ef40 */
extern undefined *PTR_FUN_10028b80; /* used by 2 fn(s), first 0x1000ef40 */
extern undefined *PTR_FUN_10028b84; /* used by 2 fn(s), first 0x1000ef40 */
extern undefined *PTR_FUN_10028b88; /* used by 1 fn(s), first 0x1000ef40 */
extern undefined *PTR_FUN_10028b8c; /* used by 1 fn(s), first 0x1000ef40 */
extern undefined4 DAT_10028ba0; /* used by 4 fn(s), first 0x10013f40 */
extern undefined *PTR_terminate_10028ba4; /* used by 1 fn(s), first 0x100141b0 */
extern undefined *PTR_DAT_10028ba8; /* used by 1 fn(s), first 0x10014370 */
extern undefined *PTR_DAT_10028bac; /* used by 1 fn(s), first 0x10014370 */
extern undefined4 DAT_10028bb0; /* used by 3 fn(s), first 0x10014e60 */
extern undefined *PTR_DAT_10028bb4; /* used by 2 fn(s), first 0x10014e30 */
extern undefined *PTR_DAT_10028bd4; /* used by 2 fn(s), first 0x10014e30 */
extern undefined *PTR_DAT_10028be4; /* used by 2 fn(s), first 0x10014e30 */
extern undefined *PTR_DAT_10028bf4; /* used by 2 fn(s), first 0x10014e30 */
extern undefined DAT_10028c70; /* used by 2 fn(s), first 0x10014240 */
extern undefined *PTR_s_No_error_10028c98; /* used by 1 fn(s), first 0x1000fec0 */
extern int DAT_10028d48; /* used by 1 fn(s), first 0x1000fec0 */
extern undefined *PTR_DAT_10028d5c; /* used by 1 fn(s), first 0x10015b30 */
extern undefined4 DAT_10028d68; /* used by 3 fn(s), first 0x10010f70 */
extern undefined4 DAT_10028d6c; /* used by 4 fn(s), first 0x10010f70 */
extern undefined4 DAT_10028d70; /* used by 4 fn(s), first 0x10010f70 */
extern undefined *PTR_DAT_10028df8; /* used by 2 fn(s), first 0x10010540 */
extern undefined *PTR_DAT_10028dfc; /* used by 1 fn(s), first 0x10016230 */
extern uint DAT_10028e00; /* used by 3 fn(s), first 0x10016230 */
extern int DAT_10028e04; /* used by 2 fn(s), first 0x10016540 */
extern undefined4 DAT_10028e08; /* used by 2 fn(s), first 0x10016540 */
extern uint DAT_10028e10; /* used by 3 fn(s), first 0x10016230 */
extern int DAT_10028e14; /* used by 2 fn(s), first 0x10016540 */
extern undefined4 DAT_10028e18; /* used by 2 fn(s), first 0x10016540 */
extern undefined2 DAT_100290e0; /* used by 1 fn(s), first 0x100184f0 */
extern undefined DAT_100290f4; /* used by 1 fn(s), first 0x100184f0 */
extern undefined DAT_100295a0; /* used by 1 fn(s), first 0x10018db6 */
extern undefined DAT_100295bc; /* used by 1 fn(s), first 0x10018c77 */
extern undefined4 DAT_100295d0; /* used by 1 fn(s), first 0x10019850 */
extern undefined4 DAT_100296a8; /* used by 2 fn(s), first 0x10019440 */
extern undefined4 DAT_100296ac; /* used by 2 fn(s), first 0x10019440 */
extern undefined4 DAT_100296b0; /* used by 1 fn(s), first 0x1001ad40 */
extern undefined4 DAT_100296b4; /* used by 1 fn(s), first 0x1001ad40 */
extern undefined4 DAT_100296b8; /* used by 1 fn(s), first 0x10019440 */
extern undefined4 DAT_100296bc; /* used by 1 fn(s), first 0x10019440 */
extern undefined4 DAT_100296c8; /* used by 1 fn(s), first 0x1001ad40 */
extern undefined4 DAT_100296cc; /* used by 1 fn(s), first 0x1001ad40 */
extern undefined DAT_10029724; /* used by 1 fn(s), first 0x1001a7ac */
extern undefined DAT_1002973c; /* used by 1 fn(s), first 0x1001a5a6 */
extern char s_____100298ac[]; /* used by 1 fn(s), first 0x1001b2d0 */
extern undefined DAT_100298b4; /* used by 1 fn(s), first 0x1001b2d0 */
extern undefined DAT_100298b8; /* used by 1 fn(s), first 0x1001cc00 */
extern undefined4 DAT_100298c0; /* used by 1 fn(s), first 0x1001cc00 */
extern undefined DAT_100299b0; /* used by 1 fn(s), first 0x1001cc00 */
extern undefined4 DAT_100299b8; /* used by 1 fn(s), first 0x1001d340 */
extern undefined DAT_10029a48; /* used by 2 fn(s), first 0x1001d340 */
extern undefined DAT_10029a60; /* used by 1 fn(s), first 0x1001db30 */
extern undefined DAT_10029a78; /* used by 2 fn(s), first 0x10013fd0 */
extern undefined4 DAT_10029af0; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_10029af4; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_10029afc; /* used by 1 fn(s), first 0x10020cb0 */
extern undefined *PTR_LOOP_10029b00; /* used by 5 fn(s), first 0x1001d2b0 */
extern undefined *PTR_LOOP_10029b04; /* used by 2 fn(s), first 0x1001e5e0 */
extern undefined4 DAT_10029b10; /* used by 2 fn(s), first 0x1001e5e0 */
extern undefined *PTR_LOOP_1002bb20; /* used by 2 fn(s), first 0x1001e750 */
extern undefined4 DAT_1002bb24; /* used by 3 fn(s), first 0x10015440 */
extern undefined DAT_1002bb2c; /* used by 1 fn(s), first 0x100167b0 */
extern undefined DAT_1002bb30; /* used by 2 fn(s), first 0x100167b0 */
extern undefined DAT_1002bb64; /* used by 2 fn(s), first 0x100167b0 */
extern undefined4 DAT_1002bb68; /* used by 2 fn(s), first 0x100167b0 */
extern undefined DAT_1002bba0; /* used by 1 fn(s), first 0x100173f0 */
extern undefined *PTR_DAT_1002bba8; /* used by 1 fn(s), first 0x100175f0 */
extern undefined *PTR_DAT_1002bbac; /* used by 1 fn(s), first 0x100175f0 */
extern undefined *PTR_DAT_1002bbb0; /* used by 1 fn(s), first 0x100175f0 */
extern undefined *PTR_PTR_1002bbd8; /* used by 2 fn(s), first 0x100173f0 */
extern undefined4 DAT_1002bbe0; /* used by 3 fn(s), first 0x10018ff0 */
extern code *g_dwSaveFunc; /* used by 2 fn(s), first 0x10002670 */
extern undefined4 g_dwLua_totalBytesSaved; /* used by 2 fn(s), first 0x10002660 */
extern undefined4 g_dwLuaHS; /* used by 55 fn(s), first 0x10001000 */
extern undefined4 g_nLuaInitialize; /* used by 2 fn(s), first 0x10001190 */
extern undefined4 g_nLuaStartup; /* used by 2 fn(s), first 0x10002920 */
extern int * g_dwFirstFuncArray; /* used by 4 fn(s), first 0x10001000 */
extern undefined DAT_1002bedc; /* used by 8 fn(s), first 0x10002440 */
extern int g_dwLState_last_tag; /* used by 7 fn(s), first 0x100079d0 */
extern int g_dwLState_nblocks; /* used by 15 fn(s), first 0x100049b0 */
extern undefined4 g_dwLState_IMtable_size; /* used by 5 fn(s), first 0x100079d0 */
extern undefined4 g_dwLState_string_root; /* used by 8 fn(s), first 0x100079d0 */
extern undefined4 g_dwLState_protoPtrTotal; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_Mbuffbase; /* used by 9 fn(s), first 0x10002c50 */
extern int * g_dwLState_rootglobal; /* used by 10 fn(s), first 0x10002db0 */
extern undefined DAT_1002bf04; /* used by 1 fn(s), first 0x10008a00 */
extern uint g_dwLState_refSize; /* used by 8 fn(s), first 0x10004d40 */
extern undefined DAT_1002bf0c; /* used by 1 fn(s), first 0x100081c0 */
extern undefined4 g_dwLState_aTablePtrs; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_roottable; /* used by 7 fn(s), first 0x10004ee0 */
extern undefined DAT_1002bf1c; /* used by 1 fn(s), first 0x10008a00 */
extern undefined4 g_dwLState_rootcl; /* used by 6 fn(s), first 0x10004ba0 */
extern undefined DAT_1002bf24; /* used by 1 fn(s), first 0x10008a00 */
extern undefined4 g_dwLState_Mbuffsize; /* used by 7 fn(s), first 0x10002c20 */
extern undefined4 g_dwLState_tablePtrTotal; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_stringPtrTotal; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_refArray; /* used by 9 fn(s), first 0x10004d40 */
extern undefined4 g_dwLState_rootproto; /* used by 6 fn(s), first 0x10004bf0 */
extern undefined DAT_1002bf3c; /* used by 1 fn(s), first 0x10008a00 */
extern undefined4 g_dwLState_Mbuffer; /* used by 12 fn(s), first 0x10002c20 */
extern undefined4 g_dwLState_aStringPtrs; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_IMtable; /* used by 20 fn(s), first 0x10004180 */
extern undefined4 g_dwLState_Mbuffnext; /* used by 12 fn(s), first 0x10002c20 */
extern undefined4 g_dwLState_closurePtrTotal; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_errorim; /* used by 5 fn(s), first 0x100014c0 */
extern undefined4 DAT_1002bf5c; /* used by 4 fn(s), first 0x100014c0 */
extern undefined4 * g_dwLState_aClosurePtrs; /* used by 4 fn(s), first 0x10007660 */
extern undefined4 g_dwLState_GCthreshold; /* used by 7 fn(s), first 0x100049b0 */
extern undefined4 * g_dwLState_aProtoPtrs; /* used by 4 fn(s), first 0x10007660 */
extern int * g_pLuaState; /* used by 117 fn(s), first 0x100011e0 */
extern int * g_dwL_Main; /* used by 11 fn(s), first 0x10001db0 */
extern undefined4 g_dwLState_lstate_class_initialized; /* used by 4 fn(s), first 0x100079d0 */
extern undefined4 g_dwLState_numThreads; /* used by 4 fn(s), first 0x10002760 */
extern undefined4 g_dwLState_bPtrsSorted; /* used by 2 fn(s), first 0x10007660 */
extern undefined4 DAT_1002bf80; /* used by 1 fn(s), first 0x1000cc30 */
extern void * g_pExecutionState_pFreeStates; /* used by 3 fn(s), first 0x1000db10 */
extern undefined4 DAT_1002bf88; /* used by 3 fn(s), first 0x10011d6d */
extern undefined DAT_1002bf8c; /* used by 2 fn(s), first 0x1000ef20 */
extern undefined4 DAT_1002bf90; /* used by 2 fn(s), first 0x10015060 */
extern undefined DAT_1002bf98; /* used by 1 fn(s), first 0x1000fec0 */
extern undefined DAT_1002bfc0; /* used by 2 fn(s), first 0x10010100 */
extern undefined DAT_1002bfd0; /* used by 1 fn(s), first 0x10010220 */
extern undefined4 DAT_1002bfe0; /* used by 2 fn(s), first 0x100103f0 */
extern undefined4 DAT_1002bfe4; /* used by 3 fn(s), first 0x10010540 */
extern undefined4 DAT_1002bfe8; /* used by 1 fn(s), first 0x10011160 */
extern undefined2 DAT_1002bff0; /* used by 1 fn(s), first 0x10011160 */
extern undefined2 DAT_1002bff2; /* used by 1 fn(s), first 0x10011160 */
extern undefined DAT_1002bff4; /* used by 1 fn(s), first 0x10011160 */
extern undefined2 DAT_1002bff6; /* used by 1 fn(s), first 0x10011160 */
extern undefined2 DAT_1002bff8; /* used by 1 fn(s), first 0x10011160 */
extern undefined2 DAT_1002bffa; /* used by 1 fn(s), first 0x10011160 */
extern undefined DAT_1002bffc; /* used by 1 fn(s), first 0x10011160 */
extern undefined4 DAT_1002c000; /* used by 1 fn(s), first 0x100117e0 */
extern undefined2 DAT_1002c004; /* used by 1 fn(s), first 0x100117e0 */
extern undefined4 DAT_1002c008; /* used by 1 fn(s), first 0x100117e0 */
extern undefined4 DAT_1002c00c; /* used by 2 fn(s), first 0x10012cb0 */
extern undefined4 * DAT_1002c010; /* used by 3 fn(s), first 0x10012cb0 */
extern undefined4 DAT_1002c018; /* used by 3 fn(s), first 0x10012e80 */
extern undefined4 DAT_1002c01c; /* used by 4 fn(s), first 0x10012e80 */
extern undefined4 DAT_1002c080; /* used by 1 fn(s), first 0x10015060 */
extern undefined4 DAT_1002c08c; /* used by 2 fn(s), first 0x1000ffd0 */
extern undefined DAT_1002c090; /* used by 1 fn(s), first 0x10012cb0 */
extern undefined DAT_1002c094; /* used by 1 fn(s), first 0x10012cb0 */
extern undefined DAT_1002c098; /* used by 1 fn(s), first 0x10012cb0 */
extern undefined DAT_1002c09c; /* used by 1 fn(s), first 0x1001c950 */
extern undefined DAT_1002c0a0; /* used by 1 fn(s), first 0x1001c950 */
extern int * DAT_1002c0a8; /* used by 4 fn(s), first 0x10010340 */
extern undefined4 DAT_1002c0ac; /* used by 1 fn(s), first 0x1001fa40 */
extern int * DAT_1002c0b0; /* used by 3 fn(s), first 0x10010340 */
extern undefined DAT_1002c0b8; /* used by 1 fn(s), first 0x1001c950 */
extern undefined DAT_1002c0c0; /* used by 2 fn(s), first 0x1000fea0 */
extern undefined4 DAT_1002c0c4; /* used by 2 fn(s), first 0x10012cb0 */
extern undefined4 DAT_1002c0c8; /* used by 1 fn(s), first 0x100155f0 */
extern undefined4 DAT_1002c0d8; /* used by 2 fn(s), first 0x10016230 */
extern undefined4 DAT_1002c0e0; /* used by 1 fn(s), first 0x10016230 */
extern undefined DAT_1002c0e4; /* used by 1 fn(s), first 0x10016230 */
extern undefined2 DAT_1002c124; /* used by 1 fn(s), first 0x10016540 */
extern undefined2 DAT_1002c126; /* used by 2 fn(s), first 0x10016230 */
extern undefined4 DAT_1002c128; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c12c; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c130; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c134; /* used by 1 fn(s), first 0x10016230 */
extern undefined DAT_1002c138; /* used by 1 fn(s), first 0x10016230 */
extern undefined2 DAT_1002c178; /* used by 1 fn(s), first 0x10016540 */
extern undefined2 DAT_1002c17a; /* used by 2 fn(s), first 0x10016230 */
extern undefined4 DAT_1002c17c; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c180; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c184; /* used by 1 fn(s), first 0x10016540 */
extern undefined4 DAT_1002c188; /* used by 1 fn(s), first 0x10016230 */
extern byte * DAT_1002c18c; /* used by 1 fn(s), first 0x10016230 */
extern undefined4 DAT_1002c190; /* used by 1 fn(s), first 0x100161f0 */
extern undefined DAT_1002c198; /* used by 1 fn(s), first 0x10016a20 */
extern undefined DAT_1002c1bc; /* used by 1 fn(s), first 0x10016c80 */
extern undefined4 DAT_1002c1c0; /* used by 1 fn(s), first 0x100173f0 */
extern undefined4 DAT_1002c1c4; /* used by 1 fn(s), first 0x100173f0 */
extern undefined4 DAT_1002c1c8; /* used by 1 fn(s), first 0x100173f0 */
extern int * DAT_1002c1cc; /* used by 1 fn(s), first 0x100175f0 */
extern undefined4 DAT_1002c1d0; /* used by 1 fn(s), first 0x100178e0 */
extern undefined4 DAT_1002c1d4; /* used by 1 fn(s), first 0x100178e0 */
extern undefined DAT_1002c1d8; /* used by 1 fn(s), first 0x10011560 */
extern undefined DAT_1002c1dc; /* used by 1 fn(s), first 0x10011560 */
extern undefined2 DAT_1002c1e4; /* used by 1 fn(s), first 0x100178e0 */
extern undefined2 DAT_1002c1ec; /* used by 1 fn(s), first 0x100176e0 */
extern undefined2 DAT_1002c1f2; /* used by 1 fn(s), first 0x100173f0 */
extern undefined DAT_1002c1f6; /* used by 1 fn(s), first 0x10016d30 */
extern undefined DAT_1002c1f8; /* used by 1 fn(s), first 0x10016d30 */
extern undefined DAT_1002c200; /* used by 1 fn(s), first 0x10011560 */
extern undefined4 DAT_1002c204; /* used by 1 fn(s), first 0x10012af0 */
extern int DAT_1002c208; /* used by 15 fn(s), first 0x10011bc0 */
extern undefined4 DAT_1002c20c; /* used by 1 fn(s), first 0x100175f0 */
extern undefined4 DAT_1002c210; /* used by 1 fn(s), first 0x100173f0 */
extern undefined DAT_1002c214; /* used by 1 fn(s), first 0x10016c80 */
extern int DAT_1002c218; /* used by 13 fn(s), first 0x10011560 */
extern undefined4 DAT_1002c21c; /* used by 6 fn(s), first 0x10017c50 */
extern undefined4 DAT_1002c220; /* used by 3 fn(s), first 0x10017e50 */
extern undefined4 DAT_1002c224; /* used by 4 fn(s), first 0x10017e50 */
extern undefined4 DAT_1002c228; /* used by 4 fn(s), first 0x10017e50 */
extern char * DAT_1002c22c; /* used by 6 fn(s), first 0x10017c50 */
extern char * DAT_1002c230; /* used by 5 fn(s), first 0x10017c50 */
extern undefined4 DAT_1002c234; /* used by 8 fn(s), first 0x10017c50 */
extern undefined4 DAT_1002c238; /* used by 6 fn(s), first 0x10017c50 */
extern code *DAT_1002c23c; /* used by 6 fn(s), first 0x10017c50 */
extern undefined4 DAT_1002c240; /* used by 1 fn(s), first 0x10018790 */
extern undefined4 DAT_1002c244; /* used by 1 fn(s), first 0x100189e0 */
extern undefined4 DAT_1002c248; /* used by 1 fn(s), first 0x1001b000 */
extern int DAT_1002c24c; /* used by 1 fn(s), first 0x1001b190 */
extern undefined4 DAT_1002c254; /* used by 1 fn(s), first 0x1001c0f0 */
extern undefined4 DAT_1002c258; /* used by 1 fn(s), first 0x1001c5f0 */
extern undefined4 DAT_1002c25c; /* used by 1 fn(s), first 0x1001c720 */
extern undefined DAT_1002c260; /* used by 1 fn(s), first 0x1001c950 */
extern undefined4 DAT_1002c368; /* used by 6 fn(s), first 0x10016020 */
extern undefined DAT_1002c470; /* used by 1 fn(s), first 0x1001cf20 */
extern undefined4 DAT_1002c570; /* used by 6 fn(s), first 0x10016020 */
extern undefined4 DAT_1002c574; /* used by 4 fn(s), first 0x10016130 */
extern undefined DAT_1002c578; /* used by 2 fn(s), first 0x1001cc00 */
extern undefined DAT_1002c57c; /* used by 2 fn(s), first 0x1001cc00 */
extern undefined DAT_1002c580; /* used by 2 fn(s), first 0x1001cc00 */
extern undefined4 DAT_1002c584; /* used by 2 fn(s), first 0x1001cc00 */
extern undefined4 DAT_1002c58c; /* used by 1 fn(s), first 0x1001d110 */
extern code *DAT_1002c590; /* used by 1 fn(s), first 0x1001d300 */
extern undefined DAT_1002c594; /* used by 3 fn(s), first 0x1001ddd0 */
extern code *DAT_1002c598; /* used by 1 fn(s), first 0x1001e5c0 */
extern undefined4 DAT_1002c59c; /* used by 3 fn(s), first 0x10015440 */
extern undefined4 DAT_1002c5a0; /* used by 2 fn(s), first 0x1001e7b0 */
extern undefined DAT_1002c5a8; /* used by 1 fn(s), first 0x10020090 */
extern undefined DAT_1002c5b0; /* used by 1 fn(s), first 0x10017870 */
extern code *DAT_1002c5b4; /* used by 1 fn(s), first 0x10020a10 */
extern code *DAT_1002c5b8; /* used by 1 fn(s), first 0x10020a10 */
extern code *DAT_1002c5bc; /* used by 1 fn(s), first 0x10020a10 */
extern undefined4 DAT_1002c5c0; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_1002c5c4; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_1002c5c8; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_1002c5cc; /* used by 1 fn(s), first 0x10020aa0 */
extern undefined4 DAT_1002c5d4; /* used by 8 fn(s), first 0x10015440 */
extern undefined DAT_1002c5d8; /* used by 2 fn(s), first 0x1001cc00 */
extern undefined4 DAT_1002c5dc; /* used by 1 fn(s), first 0x100155f0 */
extern undefined4 * DAT_1002c5e0; /* used by 1 fn(s), first 0x100155f0 */
extern int * PTR_1002c600; /* used by 21 fn(s), first 0x1000fde0 */
extern undefined4 DAT_1002c604; /* used by 1 fn(s), first 0x100151d0 */
extern undefined4 DAT_1002c700; /* used by 10 fn(s), first 0x100151d0 */
extern undefined4 * DAT_1002c704; /* used by 2 fn(s), first 0x10012cb0 */
extern code *DAT_1002c708; /* used by 1 fn(s), first 0x10012dd0 */
extern undefined4 DAT_1002c70c; /* used by 11 fn(s), first 0x100103f0 */
extern int DAT_1002c710; /* used by 3 fn(s), first 0x10011290 */
extern undefined DAT_1002c714; /* used by 4 fn(s), first 0x1000fde0 */
extern undefined DAT_1002d720; /* used by 4 fn(s), first 0x1000fde0 */
extern undefined4 in_stack_ffffffa8; /* used by 1 fn(s), first 0x100046e0 */
extern undefined4 in_stack_ffffffac; /* used by 1 fn(s), first 0x100046e0 */
extern undefined4 in_stack_ffffffb8; /* used by 1 fn(s), first 0x10004a50 */
extern undefined4 in_stack_ffffffbc; /* used by 1 fn(s), first 0x1001dc70 */

/* ---- re-typed views of the symbols above ---- */
#define _DAT_10028940 (*(undefined4 *)&DAT_10028940) /* same address as DAT_10028940, other width */
#define _DAT_10028b64 (*(undefined4 *)&DAT_10028b64) /* same address as DAT_10028b64, other width */
#define _DAT_100295a0 (*(unkbyte10 *)&DAT_100295a0) /* same address as DAT_100295a0, other width */
#define _DAT_10029724 (*(undefined4 *)&DAT_10029724) /* same address as DAT_10029724, other width */
#define _DAT_1002973c (*(undefined4 *)&DAT_1002973c) /* same address as DAT_1002973c, other width */
#define _DAT_1002bf04 (*(undefined4 *)&DAT_1002bf04) /* same address as DAT_1002bf04, other width */
#define _DAT_1002bf0c (*(undefined4 *)&DAT_1002bf0c) /* same address as DAT_1002bf0c, other width */
#define _DAT_1002bf1c (*(undefined4 *)&DAT_1002bf1c) /* same address as DAT_1002bf1c, other width */
#define _DAT_1002bf24 (*(undefined4 *)&DAT_1002bf24) /* same address as DAT_1002bf24, other width */
#define _DAT_1002bf3c (*(undefined4 *)&DAT_1002bf3c) /* same address as DAT_1002bf3c, other width */
#define _DAT_1002bf8c (*(undefined4 *)&DAT_1002bf8c) /* same address as DAT_1002bf8c, other width */
#define _DAT_1002bff0 (*(undefined2 *)&DAT_1002bff0) /* same address as DAT_1002bff0, other width */
#define _DAT_1002bff4 (*(undefined4 *)&DAT_1002bff4) /* same address as DAT_1002bff4, other width */
#define _DAT_1002bff8 (*(undefined2 *)&DAT_1002bff8) /* same address as DAT_1002bff8, other width */
#define _DAT_1002bffc (*(undefined4 *)&DAT_1002bffc) /* same address as DAT_1002bffc, other width */
#define _DAT_1002c004 (*(undefined2 *)&DAT_1002c004) /* same address as DAT_1002c004, other width */
#define _DAT_1002c090 (*(undefined4 *)&DAT_1002c090) /* same address as DAT_1002c090, other width */
#define _DAT_1002c094 (*(undefined4 *)&DAT_1002c094) /* same address as DAT_1002c094, other width */
#define _DAT_1002c098 (*(undefined4 *)&DAT_1002c098) /* same address as DAT_1002c098, other width */
#define _DAT_1002c09c (*(undefined4 *)&DAT_1002c09c) /* same address as DAT_1002c09c, other width */
#define _DAT_1002c0a0 (*(undefined4 *)&DAT_1002c0a0) /* same address as DAT_1002c0a0, other width */
#define _DAT_1002c0b8 (*(undefined4 *)&DAT_1002c0b8) /* same address as DAT_1002c0b8, other width */
#define _DAT_1002c1bc (*(int * *)&DAT_1002c1bc) /* same address as DAT_1002c1bc, other width */
#define _DAT_1002c1f6 (*(undefined2 *)&DAT_1002c1f6) /* same address as DAT_1002c1f6, other width */
#define _DAT_1002c1f8 (*(undefined2 *)&DAT_1002c1f8) /* same address as DAT_1002c1f8, other width */
#define _DAT_1002c214 (*(undefined4 *)&DAT_1002c214) /* same address as DAT_1002c214, other width */
#define _DAT_1002c578 (*(undefined4 *)&DAT_1002c578) /* same address as DAT_1002c578, other width */
#define _DAT_1002c57c (*(undefined4 *)&DAT_1002c57c) /* same address as DAT_1002c57c, other width */
#define _DAT_1002c580 (*(undefined4 *)&DAT_1002c580) /* same address as DAT_1002c580, other width */
#define _DAT_1002c594 (*(code * *)&DAT_1002c594) /* same address as DAT_1002c594, other width */
#define _DAT_1002c5d8 (*(undefined4 *)&DAT_1002c5d8) /* same address as DAT_1002c5d8, other width */
#define _DAT_1002c714 (*(undefined4 *)&DAT_1002c714) /* same address as DAT_1002c714, other width */
#define _DAT_1002d720 (*(undefined4 *)&DAT_1002d720) /* same address as DAT_1002d720, other width */
