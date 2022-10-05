// HASH COLLISIONS: YES
// timestamp: 1.664894312862E12

package main;

import com.area9innovation.flow.*;

public class Struct_Term extends Struct {
	public String f_name;

	public Struct_Term() {}
	public Struct_Term(String a_name) {
		f_name = a_name;
	}

	public int getTypeId() { return 106; }
	public String getTypeName() { return "Term"; }

	private static final String[] field_names = new String[] {
		"name"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.STRING
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_name
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Term");
		f_name = (String)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 106) return 106-tmp;
		Struct_Term other = (Struct_Term)other_gen;
		tmp = f_name.compareTo(other.f_name);
		return tmp;
	}
}
