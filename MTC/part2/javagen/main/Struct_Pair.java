// HASH COLLISIONS: YES
// timestamp: 1.66489431285E12

package main;

import com.area9innovation.flow.*;

public class Struct_Pair extends Struct implements Field_first<Object>, Field_second<Object> {
	public Object f_first;
	public Object f_second;

	public Struct_Pair() {}
	public Struct_Pair(Object a_first, Object a_second) {
		f_first = a_first;
		f_second = a_second;
	}
	public Object get_first() { return f_first; }
	public void set_first(Object value) { f_first = value; }
	public Object get_second() { return f_second; }
	public void set_second(Object value) { f_second = value; }

	public int getTypeId() { return 43; }
	public String getTypeName() { return "Pair"; }

	private static final String[] field_names = new String[] {
		"first", "second"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.UNKNOWN, RuntimeType.UNKNOWN
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_first, f_second
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 2)
			throw new IndexOutOfBoundsException("Invalid field count in Pair");
		f_first = (Object)values[0];
		f_second = (Object)values[1];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 43) return 43-tmp;
		Struct_Pair other = (Struct_Pair)other_gen;
		tmp = FlowRuntime.compareByValue(f_first, other.f_first);
		if (tmp != 0) return tmp;
		tmp = FlowRuntime.compareByValue(f_second, other.f_second);
		return tmp;
	}
}
