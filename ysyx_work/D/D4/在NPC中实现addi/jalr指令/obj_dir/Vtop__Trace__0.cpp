// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_dtype____0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp, uint32_t offset, const VlUnpacked<CData/*3:0*/, 16>& __VdtypeVar);

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlWide<16>/*511:0*/ __Vtemp_14;
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[0U]))) {
        Vtop___024root__trace_chg_dtype____0(vlSelf, bufp, 0, vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__key_list);
        Vtop___024root__trace_chg_dtype____0(vlSelf, bufp, 16, vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__key_list);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+32,(vlSelfRef.top__DOT__imm),32);
        bufp->chgBit(oldp+33,(vlSelfRef.top__DOT__jump_en));
        bufp->chgBit(oldp+34,(vlSelfRef.top__DOT__wen));
        bufp->chgSData(oldp+35,((0x00007fffU & ((IData)(vlSelfRef.top__DOT__gpr__DOT__dec1__DOT__pout) 
                                                >> 1U))),15);
        bufp->chgSData(oldp+36,(vlSelfRef.top__DOT__gpr__DOT__reg_wen),15);
        bufp->chgSData(oldp+37,(vlSelfRef.top__DOT__gpr__DOT__dec1__DOT__pout),16);
        bufp->chgBit(oldp+38,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__hit));
        bufp->chgBit(oldp+39,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__hit));
        bufp->chgBit(oldp+40,((1U & (IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen))));
        bufp->chgBit(oldp+41,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 9U))));
        bufp->chgBit(oldp+42,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 0x0000000aU))));
        bufp->chgBit(oldp+43,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 0x0000000bU))));
        bufp->chgBit(oldp+44,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 0x0000000cU))));
        bufp->chgBit(oldp+45,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 0x0000000dU))));
        bufp->chgBit(oldp+46,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 0x0000000eU))));
        bufp->chgBit(oldp+47,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 1U))));
        bufp->chgBit(oldp+48,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 2U))));
        bufp->chgBit(oldp+49,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 3U))));
        bufp->chgBit(oldp+50,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 4U))));
        bufp->chgBit(oldp+51,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 5U))));
        bufp->chgBit(oldp+52,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 6U))));
        bufp->chgBit(oldp+53,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 7U))));
        bufp->chgBit(oldp+54,((1U & ((IData)(vlSelfRef.top__DOT__gpr__DOT__reg_wen) 
                                     >> 8U))));
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgIData(oldp+55,(vlSelfRef.top__DOT__rdata1),32);
        bufp->chgIData(oldp+56,(vlSelfRef.top__DOT__rdata2),32);
        bufp->chgIData(oldp+57,(vlSelfRef.top__DOT__alu_result),32);
        bufp->chgIData(oldp+58,(vlSelfRef.top__DOT__wdata),32);
        bufp->chgIData(oldp+59,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__lut_out),32);
        bufp->chgIData(oldp+60,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__lut_out),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[2U]))) {
        __Vtemp_14[0U] = 0U;
        __Vtemp_14[1U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg1____pinNumber4;
        __Vtemp_14[2U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg2____pinNumber4;
        __Vtemp_14[3U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg3____pinNumber4;
        __Vtemp_14[4U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg4____pinNumber4;
        __Vtemp_14[5U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg5____pinNumber4;
        __Vtemp_14[6U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg6____pinNumber4;
        __Vtemp_14[7U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg7____pinNumber4;
        __Vtemp_14[8U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg8____pinNumber4;
        __Vtemp_14[9U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg9____pinNumber4;
        __Vtemp_14[10U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg10____pinNumber4;
        __Vtemp_14[11U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg11____pinNumber4;
        __Vtemp_14[12U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg12____pinNumber4;
        __Vtemp_14[13U] = vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg13____pinNumber4;
        __Vtemp_14[14U] = (IData)((((QData)((IData)(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg15____pinNumber4)) 
                                    << 0x00000020U) 
                                   | (QData)((IData)(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg14____pinNumber4))));
        __Vtemp_14[15U] = (IData)(((((QData)((IData)(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg15____pinNumber4)) 
                                     << 0x00000020U) 
                                    | (QData)((IData)(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg14____pinNumber4))) 
                                   >> 0x00000020U));
        bufp->chgWData(oldp+61,(__Vtemp_14),512);
        bufp->chgWData(oldp+77,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__lut),576);
        bufp->chgQData(oldp+95,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[15]),36);
        bufp->chgQData(oldp+97,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[14]),36);
        bufp->chgQData(oldp+99,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[13]),36);
        bufp->chgQData(oldp+101,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[12]),36);
        bufp->chgQData(oldp+103,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[11]),36);
        bufp->chgQData(oldp+105,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[10]),36);
        bufp->chgQData(oldp+107,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[9]),36);
        bufp->chgQData(oldp+109,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[8]),36);
        bufp->chgQData(oldp+111,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[7]),36);
        bufp->chgQData(oldp+113,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[6]),36);
        bufp->chgQData(oldp+115,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[5]),36);
        bufp->chgQData(oldp+117,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[4]),36);
        bufp->chgQData(oldp+119,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[3]),36);
        bufp->chgQData(oldp+121,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[2]),36);
        bufp->chgQData(oldp+123,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[1]),36);
        bufp->chgQData(oldp+125,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__pair_list[0]),36);
        bufp->chgIData(oldp+127,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[15]),32);
        bufp->chgIData(oldp+128,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[14]),32);
        bufp->chgIData(oldp+129,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[13]),32);
        bufp->chgIData(oldp+130,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[12]),32);
        bufp->chgIData(oldp+131,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[11]),32);
        bufp->chgIData(oldp+132,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[10]),32);
        bufp->chgIData(oldp+133,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[9]),32);
        bufp->chgIData(oldp+134,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[8]),32);
        bufp->chgIData(oldp+135,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[7]),32);
        bufp->chgIData(oldp+136,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[6]),32);
        bufp->chgIData(oldp+137,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[5]),32);
        bufp->chgIData(oldp+138,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[4]),32);
        bufp->chgIData(oldp+139,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[3]),32);
        bufp->chgIData(oldp+140,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[2]),32);
        bufp->chgIData(oldp+141,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[1]),32);
        bufp->chgIData(oldp+142,(vlSelfRef.top__DOT__gpr__DOT__mux1__DOT__i0__DOT__i0__DOT__data_list[0]),32);
        bufp->chgQData(oldp+143,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[15]),36);
        bufp->chgQData(oldp+145,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[14]),36);
        bufp->chgQData(oldp+147,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[13]),36);
        bufp->chgQData(oldp+149,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[12]),36);
        bufp->chgQData(oldp+151,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[11]),36);
        bufp->chgQData(oldp+153,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[10]),36);
        bufp->chgQData(oldp+155,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[9]),36);
        bufp->chgQData(oldp+157,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[8]),36);
        bufp->chgQData(oldp+159,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[7]),36);
        bufp->chgQData(oldp+161,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[6]),36);
        bufp->chgQData(oldp+163,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[5]),36);
        bufp->chgQData(oldp+165,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[4]),36);
        bufp->chgQData(oldp+167,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[3]),36);
        bufp->chgQData(oldp+169,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[2]),36);
        bufp->chgQData(oldp+171,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[1]),36);
        bufp->chgQData(oldp+173,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__pair_list[0]),36);
        bufp->chgIData(oldp+175,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[15]),32);
        bufp->chgIData(oldp+176,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[14]),32);
        bufp->chgIData(oldp+177,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[13]),32);
        bufp->chgIData(oldp+178,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[12]),32);
        bufp->chgIData(oldp+179,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[11]),32);
        bufp->chgIData(oldp+180,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[10]),32);
        bufp->chgIData(oldp+181,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[9]),32);
        bufp->chgIData(oldp+182,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[8]),32);
        bufp->chgIData(oldp+183,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[7]),32);
        bufp->chgIData(oldp+184,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[6]),32);
        bufp->chgIData(oldp+185,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[5]),32);
        bufp->chgIData(oldp+186,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[4]),32);
        bufp->chgIData(oldp+187,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[3]),32);
        bufp->chgIData(oldp+188,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[2]),32);
        bufp->chgIData(oldp+189,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[1]),32);
        bufp->chgIData(oldp+190,(vlSelfRef.top__DOT__gpr__DOT__mux2__DOT__i0__DOT__i0__DOT__data_list[0]),32);
        bufp->chgIData(oldp+191,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg1____pinNumber4),32);
        bufp->chgIData(oldp+192,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg10____pinNumber4),32);
        bufp->chgIData(oldp+193,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg11____pinNumber4),32);
        bufp->chgIData(oldp+194,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg12____pinNumber4),32);
        bufp->chgIData(oldp+195,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg13____pinNumber4),32);
        bufp->chgIData(oldp+196,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg14____pinNumber4),32);
        bufp->chgIData(oldp+197,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg15____pinNumber4),32);
        bufp->chgIData(oldp+198,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg2____pinNumber4),32);
        bufp->chgIData(oldp+199,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg3____pinNumber4),32);
        bufp->chgIData(oldp+200,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg4____pinNumber4),32);
        bufp->chgIData(oldp+201,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg5____pinNumber4),32);
        bufp->chgIData(oldp+202,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg6____pinNumber4),32);
        bufp->chgIData(oldp+203,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg7____pinNumber4),32);
        bufp->chgIData(oldp+204,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg8____pinNumber4),32);
        bufp->chgIData(oldp+205,(vlSelfRef.top__DOT__gpr__DOT____Vcellout__reg9____pinNumber4),32);
    }
    bufp->chgBit(oldp+206,(vlSelfRef.clk));
    bufp->chgBit(oldp+207,(vlSelfRef.rst));
    bufp->chgIData(oldp+208,(vlSelfRef.pc_state),32);
    bufp->chgIData(oldp+209,(vlSelfRef.instruction),32);
    bufp->chgIData(oldp+210,(vlSelfRef.m_addr),32);
    bufp->chgIData(oldp+211,(vlSelfRef.m_rdata),32);
    bufp->chgIData(oldp+212,(vlSelfRef.m_wdata),32);
    bufp->chgBit(oldp+213,(vlSelfRef.m_ren));
    bufp->chgBit(oldp+214,(vlSelfRef.m_wen));
    bufp->chgCData(oldp+215,(vlSelfRef.m_size),2);
    bufp->chgCData(oldp+216,((0x0000007fU & vlSelfRef.instruction)),7);
    bufp->chgCData(oldp+217,((7U & (vlSelfRef.instruction 
                                    >> 0x0000000cU))),3);
    bufp->chgCData(oldp+218,((vlSelfRef.instruction 
                              >> 0x00000019U)),7);
    bufp->chgCData(oldp+219,((0x0000001fU & (vlSelfRef.instruction 
                                             >> 7U))),5);
    bufp->chgCData(oldp+220,((0x0000001fU & (vlSelfRef.instruction 
                                             >> 0x0000000fU))),5);
    bufp->chgCData(oldp+221,((0x0000001fU & (vlSelfRef.instruction 
                                             >> 0x00000014U))),5);
    bufp->chgBit(oldp+222,(((~ (vlSelfRef.instruction 
                                >> 7U)) & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_10))));
    bufp->chgCData(oldp+223,((0x0000000fU & (vlSelfRef.instruction 
                                             >> 7U))),4);
    bufp->chgCData(oldp+224,(((((2U & ((~ (vlSelfRef.instruction 
                                           >> 0x0000000aU)) 
                                       << 1U)) | (1U 
                                                  & (~ 
                                                     (vlSelfRef.instruction 
                                                      >> 9U)))) 
                               << 2U) | ((2U & ((~ 
                                                 (vlSelfRef.instruction 
                                                  >> 8U)) 
                                                << 1U)) 
                                         | (1U & (~ 
                                                  (vlSelfRef.instruction 
                                                   >> 7U)))))),4);
    bufp->chgCData(oldp+225,((0x0000000fU & (vlSelfRef.instruction 
                                             >> 0x0000000fU))),4);
    bufp->chgCData(oldp+226,((0x0000000fU & (vlSelfRef.instruction 
                                             >> 0x00000014U))),4);
    bufp->chgCData(oldp+227,((0x0000001fU & (vlSelfRef.instruction 
                                             >> 0x00000014U))),5);
    bufp->chgIData(oldp+228,((((- (IData)((vlSelfRef.instruction 
                                           >> 0x0000001fU))) 
                               << 0x0000000cU) | (vlSelfRef.instruction 
                                                  >> 0x00000014U))),32);
    bufp->chgIData(oldp+229,((((- (IData)((vlSelfRef.instruction 
                                           >> 0x0000001fU))) 
                               << 0x0000000cU) | ((0x00000fe0U 
                                                   & (vlSelfRef.instruction 
                                                      >> 0x00000014U)) 
                                                  | (0x0000001fU 
                                                     & (vlSelfRef.instruction 
                                                        >> 7U))))),32);
    bufp->chgIData(oldp+230,((((- (IData)((vlSelfRef.instruction 
                                           >> 0x0000001fU))) 
                               << 0x0000000cU) | ((0x00000800U 
                                                   & (vlSelfRef.instruction 
                                                      << 4U)) 
                                                  | ((0x000007e0U 
                                                      & (vlSelfRef.instruction 
                                                         >> 0x00000014U)) 
                                                     | (0x0000001eU 
                                                        & (vlSelfRef.instruction 
                                                           >> 7U)))))),32);
    bufp->chgIData(oldp+231,((0xfffff000U & vlSelfRef.instruction)),32);
    bufp->chgIData(oldp+232,((((- (IData)((vlSelfRef.instruction 
                                           >> 0x0000001fU))) 
                               << 0x00000014U) | ((
                                                   ((0x000001feU 
                                                     & (vlSelfRef.instruction 
                                                        >> 0x0000000bU)) 
                                                    | (1U 
                                                       & (vlSelfRef.instruction 
                                                          >> 0x00000014U))) 
                                                   << 0x0000000bU) 
                                                  | (0x000007feU 
                                                     & (vlSelfRef.instruction 
                                                        >> 0x00000014U))))),32);
    bufp->chgIData(oldp+233,(((IData)(vlSelfRef.top__DOT__jump_en)
                               ? vlSelfRef.top__DOT__alu_result
                               : ((IData)(4U) + vlSelfRef.pc_state))),32);
}

void Vtop___024root__trace_chg_dtype____0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp, uint32_t offset, const VlUnpacked<CData/*3:0*/, 16>& __VdtypeVar) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_dtype____0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode +  offset);
    bufp->chgCData(oldp+0,(__VdtypeVar[15]),4);
    bufp->chgCData(oldp+1,(__VdtypeVar[14]),4);
    bufp->chgCData(oldp+2,(__VdtypeVar[13]),4);
    bufp->chgCData(oldp+3,(__VdtypeVar[12]),4);
    bufp->chgCData(oldp+4,(__VdtypeVar[11]),4);
    bufp->chgCData(oldp+5,(__VdtypeVar[10]),4);
    bufp->chgCData(oldp+6,(__VdtypeVar[9]),4);
    bufp->chgCData(oldp+7,(__VdtypeVar[8]),4);
    bufp->chgCData(oldp+8,(__VdtypeVar[7]),4);
    bufp->chgCData(oldp+9,(__VdtypeVar[6]),4);
    bufp->chgCData(oldp+10,(__VdtypeVar[5]),4);
    bufp->chgCData(oldp+11,(__VdtypeVar[4]),4);
    bufp->chgCData(oldp+12,(__VdtypeVar[3]),4);
    bufp->chgCData(oldp+13,(__VdtypeVar[2]),4);
    bufp->chgCData(oldp+14,(__VdtypeVar[1]),4);
    bufp->chgCData(oldp+15,(__VdtypeVar[0]),4);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
