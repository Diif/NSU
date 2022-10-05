// HASH COLLISIONS: YES
// timestamp: 1.664867880597E12

package main;

import com.area9innovation.flow.*;

public class Struct_pVar extends Struct {
	public String f_var;

	public Struct_pVar() {}
	public Struct_pVar(String a_var) {
		f_var = a_var;
	}

	public int getTypeId() { return 111; }
	public String getTypeName() { return "pVar"; }

	private static final String[] field_names = new String[] {
		"var"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.STRING
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_var
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in pVar");
		f_var = (String)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 111) return 111-tmp;
		Struct_pVar other = (Struct_pVar)other_gen;
		tmp = f_var.compareTo(other.f_var);
		return tmp;
	}
}
