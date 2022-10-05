// HASH COLLISIONS: YES
// timestamp: 1.664894312846E12

package main;

import com.area9innovation.flow.*;

public class Struct_JsonObject extends Struct {
	public Object[] f_members;

	public Struct_JsonObject() {}
	public Struct_JsonObject(Object[] a_members) {
		f_members = a_members;
	}

	public int getTypeId() { return 31; }
	public String getTypeName() { return "JsonObject"; }

	private static final String[] field_names = new String[] {
		"members"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.ARRAY
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_members
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in JsonObject");
		f_members = (Object[])values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 31) return 31-tmp;
		Struct_JsonObject other = (Struct_JsonObject)other_gen;
		tmp = FlowRuntime.compareByValue(f_members, other.f_members);
		return tmp;
	}
}
