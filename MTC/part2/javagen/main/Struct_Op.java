// HASH COLLISIONS: YES
// timestamp: 1.664894312849E12

package main;

import com.area9innovation.flow.*;

public class Struct_Op extends Struct {
	public String f_o;

	public Struct_Op() {}
	public Struct_Op(String a_o) {
		f_o = a_o;
	}

	public int getTypeId() { return 41; }
	public String getTypeName() { return "Op"; }

	private static final String[] field_names = new String[] {
		"o"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.STRING
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_o
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Op");
		f_o = (String)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 41) return 41-tmp;
		Struct_Op other = (Struct_Op)other_gen;
		tmp = f_o.compareTo(other.f_o);
		return tmp;
	}
}
