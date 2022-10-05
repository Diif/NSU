// HASH COLLISIONS: YES
// timestamp: 1.664614877782E12

package main;

import com.area9innovation.flow.*;

public class Struct_Name extends Struct {
	public String f_name;

	public Struct_Name() {}
	public Struct_Name(String a_name) {
		f_name = a_name;
	}

	public int getTypeId() { return 38; }
	public String getTypeName() { return "Name"; }

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
			throw new IndexOutOfBoundsException("Invalid field count in Name");
		f_name = (String)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 38) return 38-tmp;
		Struct_Name other = (Struct_Name)other_gen;
		tmp = f_name.compareTo(other.f_name);
		return tmp;
	}
}
