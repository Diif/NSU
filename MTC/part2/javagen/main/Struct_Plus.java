// HASH COLLISIONS: YES
// timestamp: 1.664894312858E12

package main;

import com.area9innovation.flow.*;

public class Struct_Plus extends Struct {
	public Struct f_p;

	public Struct_Plus() {}
	public Struct_Plus(Struct a_p) {
		f_p = a_p;
	}

	public int getTypeId() { return 90; }
	public String getTypeName() { return "Plus"; }

	private static final String[] field_names = new String[] {
		"p"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.STRUCT
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_p
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Plus");
		f_p = (Struct)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 90) return 90-tmp;
		Struct_Plus other = (Struct_Plus)other_gen;
		tmp = f_p.compareTo(other.f_p);
		return tmp;
	}
}
