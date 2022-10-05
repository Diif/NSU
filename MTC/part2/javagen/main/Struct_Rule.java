// HASH COLLISIONS: YES
// timestamp: 1.66489431286E12

package main;

import com.area9innovation.flow.*;

public class Struct_Rule extends Struct {
	public String f_name;

	public Struct_Rule() {}
	public Struct_Rule(String a_name) {
		f_name = a_name;
	}

	public int getTypeId() { return 97; }
	public String getTypeName() { return "Rule"; }

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
			throw new IndexOutOfBoundsException("Invalid field count in Rule");
		f_name = (String)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 97) return 97-tmp;
		Struct_Rule other = (Struct_Rule)other_gen;
		tmp = f_name.compareTo(other.f_name);
		return tmp;
	}
}
