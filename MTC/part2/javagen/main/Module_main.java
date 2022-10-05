// HASH COLLISIONS: YES
// timestamp: 1.664894308E12

package main;

import com.area9innovation.flow.*;

@SuppressWarnings("unchecked")
final public class Module_main {
	public static Reference<Struct> g_lingoGrammarOpAr;
	public static Reference<Struct> g_lingoGrammarOpPol;
	public static void init() {
		g_lingoGrammarOpAr=((Reference<Struct>)(new Reference(SingletonStructs.str_None)));
		g_lingoGrammarOpPol=((Reference<Struct>)(new Reference(SingletonStructs.str_None)));
	}
	public static final Object f_astToStr(Struct aexp_0) {
			Struct l0__tmp = aexp_0;
			switch (l0__tmp.getTypeId()) {
			case 110/*Val*/: {
				final Struct_Val l1__tmp = (Struct_Val)l0__tmp;
				final double l2_val = l1__tmp.f_val;
				final double l3_val = l1__tmp.f_val;
				return Native.print(Module_string.f_d2s(l3_val));
			}
			case 111/*Var*/: {
				final Struct_Var l1__tmp = (Struct_Var)l0__tmp;
				final String l4_var = l1__tmp.f_var;
				final String l5_var = l1__tmp.f_var;
				return Native.print(l5_var);
			}
			case 8/*Add*/: {
				final Struct_Add l1__tmp = (Struct_Add)l0__tmp;
				final Struct l6_e1 = l1__tmp.f_e1;
				final Struct l7_e2 = l1__tmp.f_e2;
				final Struct l8_e1 = l1__tmp.f_e1;
				final Struct l9_e2 = l1__tmp.f_e2;
				Native.print("(");
				Module_main.f_astToStr(l8_e1);
				Native.print("+");
				Module_main.f_astToStr(l9_e2);
				return Native.print(")");
			}
			case 105/*Sub*/: {
				final Struct_Sub l1__tmp = (Struct_Sub)l0__tmp;
				final Struct l10_e1 = l1__tmp.f_e1;
				final Struct l11_e2 = l1__tmp.f_e2;
				final Struct l12_e1 = l1__tmp.f_e1;
				final Struct l13_e2 = l1__tmp.f_e2;
				Native.print("(");
				Module_main.f_astToStr(l12_e1);
				Native.print("-");
				Module_main.f_astToStr(l13_e2);
				return Native.print(")");
			}
			case 16/*Div*/: {
				final Struct_Div l1__tmp = (Struct_Div)l0__tmp;
				final Struct l14_e1 = l1__tmp.f_e1;
				final Struct l15_e2 = l1__tmp.f_e2;
				final Struct l16_e1 = l1__tmp.f_e1;
				final Struct l17_e2 = l1__tmp.f_e2;
				Native.print("(");
				Module_main.f_astToStr(l16_e1);
				Native.print("/");
				Module_main.f_astToStr(l17_e2);
				return Native.print(")");
			}
			case 37/*Mul*/: {
				final Struct_Mul l1__tmp = (Struct_Mul)l0__tmp;
				final Struct l18_e1 = l1__tmp.f_e1;
				final Struct l19_e2 = l1__tmp.f_e2;
				final Struct l20_e1 = l1__tmp.f_e1;
				final Struct l21_e2 = l1__tmp.f_e2;
				Native.print("(");
				Module_main.f_astToStr(l20_e1);
				Native.print("*");
				Module_main.f_astToStr(l21_e2);
				return Native.print(")");
			}
			case 93/*Pow*/: {
				final Struct_Pow l1__tmp = (Struct_Pow)l0__tmp;
				final Struct l22_e1 = l1__tmp.f_e1;
				final Struct l23_e2 = l1__tmp.f_e2;
				final Struct l24_e1 = l1__tmp.f_e1;
				final Struct l25_e2 = l1__tmp.f_e2;
				Native.print("(");
				Module_main.f_astToStr(l24_e1);
				Native.print("^");
				Module_main.f_astToStr(l25_e2);
				return Native.print(")");
			}
			default:
				throw new RuntimeException("Unexpected struct in switch: "+l0__tmp.getTypeName());
			}
		}
	public static final double f_calculateAst(Struct aexp_0) {
			Struct l0__tmp = aexp_0;
			switch (l0__tmp.getTypeId()) {
			case 110/*Val*/: {
				final Struct_Val l1__tmp = (Struct_Val)l0__tmp;
				final double l2_val = l1__tmp.f_val;
				final double l3_val = l1__tmp.f_val;
				return l3_val;
			}
			case 111/*Var*/: {
				final Struct_Var l1__tmp = (Struct_Var)l0__tmp;
				final String l4_var = l1__tmp.f_var;
				final String l5_var = l1__tmp.f_var;
				return Module_math.f_s2d(Module_url_parameter.f_getUrlParameter(l5_var));
			}
			case 8/*Add*/: {
				final Struct_Add l1__tmp = (Struct_Add)l0__tmp;
				final Struct l6_e1 = l1__tmp.f_e1;
				final Struct l7_e2 = l1__tmp.f_e2;
				final Struct l8_e1 = l1__tmp.f_e1;
				final Struct l9_e2 = l1__tmp.f_e2;
				return (Module_main.f_calculateAst(l8_e1)+Module_main.f_calculateAst(l9_e2));
			}
			case 105/*Sub*/: {
				final Struct_Sub l1__tmp = (Struct_Sub)l0__tmp;
				final Struct l10_e1 = l1__tmp.f_e1;
				final Struct l11_e2 = l1__tmp.f_e2;
				final Struct l12_e1 = l1__tmp.f_e1;
				final Struct l13_e2 = l1__tmp.f_e2;
				return (Module_main.f_calculateAst(l12_e1)-Module_main.f_calculateAst(l13_e2));
			}
			case 16/*Div*/: {
				final Struct_Div l1__tmp = (Struct_Div)l0__tmp;
				final Struct l14_e1 = l1__tmp.f_e1;
				final Struct l15_e2 = l1__tmp.f_e2;
				final Struct l16_e1 = l1__tmp.f_e1;
				final Struct l17_e2 = l1__tmp.f_e2;
				return (Module_main.f_calculateAst(l16_e1)/Module_main.f_calculateAst(l17_e2));
			}
			case 37/*Mul*/: {
				final Struct_Mul l1__tmp = (Struct_Mul)l0__tmp;
				final Struct l18_e1 = l1__tmp.f_e1;
				final Struct l19_e2 = l1__tmp.f_e2;
				final Struct l20_e1 = l1__tmp.f_e1;
				final Struct l21_e2 = l1__tmp.f_e2;
				return (Module_main.f_calculateAst(l20_e1)*Module_main.f_calculateAst(l21_e2));
			}
			case 93/*Pow*/: {
				final Struct_Pow l1__tmp = (Struct_Pow)l0__tmp;
				final Struct l22_e1 = l1__tmp.f_e1;
				final Struct l23_e2 = l1__tmp.f_e2;
				final Struct l24_e1 = l1__tmp.f_e1;
				final Struct l25_e2 = l1__tmp.f_e2;
				return Module_math.f_dpow(Module_main.f_calculateAst(l24_e1), Module_main.f_calculateAst(l25_e2));
			}
			default:
				throw new RuntimeException("Unexpected struct in switch: "+l0__tmp.getTypeName());
			}
		}
	public static final double f_calculatePolish(Object[] astack, int atopIndex) {
			final Struct l0_elem = ((Struct)(astack[atopIndex]));
			Struct l1__tmp = l0_elem;
			switch (l1__tmp.getTypeId()) {
			case 110/*Val*/: {
				final Struct_Val l2__tmp = (Struct_Val)l1__tmp;
				final double l3_val = l2__tmp.f_val;
				final double l4_val = l2__tmp.f_val;
				return l4_val;
			}
			case 111/*Var*/: {
				final Struct_Var l2__tmp = (Struct_Var)l1__tmp;
				final String l5_var = l2__tmp.f_var;
				final String l6_var = l2__tmp.f_var;
				return Module_math.f_s2d(Module_url_parameter.f_getUrlParameter(l6_var));
			}
			case 41/*Op*/: {
				final Struct_Op l2__tmp = (Struct_Op)l1__tmp;
				final String l7_op = l2__tmp.f_o;
				final String l8_op = l2__tmp.f_o;
				if ((l8_op).equals("*")) {
					return (Module_main.f_calculatePolish(astack, (atopIndex-2))*Module_main.f_calculatePolish(astack, (atopIndex-1)));
				} else {
					if ((l8_op).equals("/")) {
						return (Module_main.f_calculatePolish(astack, (atopIndex-2))/Module_main.f_calculatePolish(astack, (atopIndex-1)));
					} else {
						if ((l8_op).equals("-")) {
							return (Module_main.f_calculatePolish(astack, (atopIndex-2))-Module_main.f_calculatePolish(astack, (atopIndex-1)));
						} else {
							if ((l8_op).equals("^")) {
								return Module_math.f_dpow(Module_main.f_calculatePolish(astack, (atopIndex-2)), Module_main.f_calculatePolish(astack, (atopIndex-1)));
							} else {
								return (Module_main.f_calculatePolish(astack, (atopIndex-2))+Module_main.f_calculatePolish(astack, (atopIndex-1)));
							}
						}
					}
				}
			}
			default:
				throw new RuntimeException("Unexpected struct in switch: "+l1__tmp.getTypeName());
			}
		}
	public static final Object[] f_lingoGrammarAr() {
			final Func0<Object[]> l1_$0 = (Func0<Object[]>)() -> {
				return Module_driver.f_compilePegGrammar("exp = \n\t  ws \"(\" ws exp:e1 ws \"+\" ws exp:e2 ws \")\" ws { Add(:e1, :e2) }\n\t| ws \"(\" ws exp:e1 ws \"-\" ws exp:e2 ws \")\" ws { Sub(:e1, :e2) }\n\t| ws \"(\" ws exp:e1 ws \"*\" ws exp:e2 ws \")\" ws { Mul(:e1, :e2) }\n\t| ws \"(\" ws exp:e1 ws \"/\" ws exp:e2 ws \")\" ws { Div(:e1, :e2) }\n\t| ws \"(\" ws exp:e1 ws \"^\" ws exp:e2 ws \")\" ws { Pow(:e1, :e2) }\n\t| ws \"(\" ws exp:e ws \")\" ws { :e }\n\t| ws ((\"-\")* digit+ (\".\" digit+)?)$d ws {Val(s2d($d))}\n\t| ws variable$v ws {Var($v)};\n\nvariable = letter+ (digit | letter)*;\nletter = 'a'-'z';\ndigit = '0'-'9';\n\nws = w*;\nw = \" \" | \"\\t\" | \"\\n\";");
			};
			return ((Object[])Module_maybe.f_onlyOnce(Module_main.g_lingoGrammarOpAr, ((Func0<Object>)(Func0)l1_$0)));
		}
	public static final Object[] f_lingoGrammarPol() {
			final Func0<Object[]> l1_$0 = (Func0<Object[]>)() -> {
				return Module_driver.f_compilePegGrammar("stack = elem+:e {:e};\nelem = ws operation$o ws {Op($o)}| ws variable$v ws {Var($v)} | ws number$n ws {Val(s2d($n))};\noperation =  \"*\" | \"+\" | \"/\" | \"-\" | \"^\";\nvariable = letter+ (digit | letter)*;\nnumber = digit+;\nletter = 'a'-'z';\ndigit = '0'-'9';\n\nws = w*;\nw = \" \" | \"\\t\" | \"\\n\";");
			};
			return ((Object[])Module_maybe.f_onlyOnce(Module_main.g_lingoGrammarOpPol, ((Func0<Object>)(Func0)l1_$0)));
		}
	public static final Object f_main() {
			final String l0_str = Module_string.f_strsubsmart(Native.readUntil("\n"), 0, (-1));
			final Object l1_resultAr = Module_parsic.f_parsic(Module_main.f_lingoGrammarAr(), l0_str, Module_pegaction.g_defaultPegActions);
			Module_runtime.f_println(l1_resultAr);
			final Struct l2_r = ((Struct)l1_resultAr);
			Module_main.f_astToStr(l2_r);
			Module_runtime.f_println("");
			Module_runtime.f_println(Module_main.f_calculateAst(((Struct)l1_resultAr)));
			final String l3_polish = Module_main.f_makeRPNString(((Struct)l1_resultAr));
			Module_runtime.f_println(l3_polish);
			final Object l4_resultPol = Module_parsic.f_parsic(Module_main.f_lingoGrammarPol(), l3_polish, Module_pegaction.g_defaultPegActions);
			Module_runtime.f_println(l4_resultPol);
			Module_runtime.f_println(Module_main.f_calculatePolish(((Object[])l4_resultPol), (Native.length(((Object[])l4_resultPol))-1)));
			return Module_runtime.f_println(Module_main.f_polishToAr(((Object[])l4_resultPol), (Native.length(((Object[])l4_resultPol))-1)));
		}
	public static final String f_makeRPNString(Struct aexp_0) {
			Struct l0__tmp = aexp_0;
			switch (l0__tmp.getTypeId()) {
			case 110/*Val*/: {
				final Struct_Val l1__tmp = (Struct_Val)l0__tmp;
				final double l2_val = l1__tmp.f_val;
				final double l3_val = l1__tmp.f_val;
				return (Module_string.f_d2s(l3_val)+" ");
			}
			case 111/*Var*/: {
				final Struct_Var l1__tmp = (Struct_Var)l0__tmp;
				final String l4_var = l1__tmp.f_var;
				final String l5_var = l1__tmp.f_var;
				return (l5_var+" ");
			}
			case 8/*Add*/: {
				final Struct_Add l1__tmp = (Struct_Add)l0__tmp;
				final Struct l6_e1 = l1__tmp.f_e1;
				final Struct l7_e2 = l1__tmp.f_e2;
				final Struct l8_e1 = l1__tmp.f_e1;
				final Struct l9_e2 = l1__tmp.f_e2;
				return ((Module_main.f_makeRPNString(l8_e1)+Module_main.f_makeRPNString(l9_e2))+"+ ");
			}
			case 105/*Sub*/: {
				final Struct_Sub l1__tmp = (Struct_Sub)l0__tmp;
				final Struct l10_e1 = l1__tmp.f_e1;
				final Struct l11_e2 = l1__tmp.f_e2;
				final Struct l12_e1 = l1__tmp.f_e1;
				final Struct l13_e2 = l1__tmp.f_e2;
				return ((Module_main.f_makeRPNString(l12_e1)+Module_main.f_makeRPNString(l13_e2))+"- ");
			}
			case 16/*Div*/: {
				final Struct_Div l1__tmp = (Struct_Div)l0__tmp;
				final Struct l14_e1 = l1__tmp.f_e1;
				final Struct l15_e2 = l1__tmp.f_e2;
				final Struct l16_e1 = l1__tmp.f_e1;
				final Struct l17_e2 = l1__tmp.f_e2;
				return ((Module_main.f_makeRPNString(l16_e1)+Module_main.f_makeRPNString(l17_e2))+"/ ");
			}
			case 37/*Mul*/: {
				final Struct_Mul l1__tmp = (Struct_Mul)l0__tmp;
				final Struct l18_e1 = l1__tmp.f_e1;
				final Struct l19_e2 = l1__tmp.f_e2;
				final Struct l20_e1 = l1__tmp.f_e1;
				final Struct l21_e2 = l1__tmp.f_e2;
				return ((Module_main.f_makeRPNString(l20_e1)+Module_main.f_makeRPNString(l21_e2))+"* ");
			}
			case 93/*Pow*/: {
				final Struct_Pow l1__tmp = (Struct_Pow)l0__tmp;
				final Struct l22_e1 = l1__tmp.f_e1;
				final Struct l23_e2 = l1__tmp.f_e2;
				final Struct l24_e1 = l1__tmp.f_e1;
				final Struct l25_e2 = l1__tmp.f_e2;
				return ((Module_main.f_makeRPNString(l24_e1)+Module_main.f_makeRPNString(l25_e2))+"^ ");
			}
			default:
				throw new RuntimeException("Unexpected struct in switch: "+l0__tmp.getTypeName());
			}
		}
	public static final String f_polishToAr(Object[] astack, int atopIndex) {
			final Struct l0_elem = ((Struct)(astack[atopIndex]));
			Struct l1__tmp = l0_elem;
			switch (l1__tmp.getTypeId()) {
			case 110/*Val*/: {
				final Struct_Val l2__tmp = (Struct_Val)l1__tmp;
				final double l3_val = l2__tmp.f_val;
				final double l4_val = l2__tmp.f_val;
				return Module_string.f_d2s(l4_val);
			}
			case 111/*Var*/: {
				final Struct_Var l2__tmp = (Struct_Var)l1__tmp;
				final String l5_var = l2__tmp.f_var;
				final String l6_var = l2__tmp.f_var;
				return l6_var;
			}
			case 41/*Op*/: {
				final Struct_Op l2__tmp = (Struct_Op)l1__tmp;
				final String l7_op = l2__tmp.f_o;
				final String l8_op = l2__tmp.f_o;
				if ((l8_op).equals("*")) {
					return (((("("+Module_main.f_polishToAr(astack, (atopIndex-2)))+"*")+Module_main.f_polishToAr(astack, (atopIndex-1)))+")");
				} else {
					if ((l8_op).equals("/")) {
						return (((("("+Module_main.f_polishToAr(astack, (atopIndex-2)))+"/")+Module_main.f_polishToAr(astack, (atopIndex-1)))+")");
					} else {
						if ((l8_op).equals("-")) {
							return (((("("+Module_main.f_polishToAr(astack, (atopIndex-2)))+"-")+Module_main.f_polishToAr(astack, (atopIndex-1)))+")");
						} else {
							if ((l8_op).equals("^")) {
								return (((("("+Module_main.f_polishToAr(astack, (atopIndex-2)))+"^")+Module_main.f_polishToAr(astack, (atopIndex-1)))+")");
							} else {
								return (((("("+Module_main.f_polishToAr(astack, (atopIndex-2)))+"+")+Module_main.f_polishToAr(astack, (atopIndex-1)))+")");
							}
						}
					}
				}
			}
			default:
				throw new RuntimeException("Unexpected struct in switch: "+l1__tmp.getTypeName());
			}
		}
}
