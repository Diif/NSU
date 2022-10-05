// HASH COLLISIONS: YES
// timestamp: 1.664894312859E12

package main;

import com.area9innovation.flow.*;

public class Struct_Promise extends Struct {
	public Func2<Object,Func1<Object,Object>, Func1<Object,Object>> f_f;

	public Struct_Promise() {}
	public Struct_Promise(Func2<Object,Func1<Object,Object>, Func1<Object,Object>> a_f) {
		f_f = a_f;
	}

	public int getTypeId() { return 95; }
	public String getTypeName() { return "Promise"; }

	private static final String[] field_names = new String[] {
		"f"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.UNKNOWN
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_f
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Promise");
		f_f = (Func2<Object,Func1<Object,Object>, Func1<Object,Object>>)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 95) return 95-tmp;
		Struct_Promise other = (Struct_Promise)other_gen;
		tmp = FlowRuntime.compareByValue(f_f, other.f_f);
		return tmp;
	}
}
