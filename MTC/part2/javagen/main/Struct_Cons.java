// HASH COLLISIONS: YES
// timestamp: 1.664894312842E12

package main;

import com.area9innovation.flow.*;

public class Struct_Cons extends Struct {
	public Object f_head;
	public Struct f_tail;

	public Struct_Cons() {}
	public Struct_Cons(Object a_head, Struct a_tail) {
		f_head = a_head;
		f_tail = a_tail;
	}

	public int getTypeId() { return 13; }
	public String getTypeName() { return "Cons"; }

	private static final String[] field_names = new String[] {
		"head", "tail"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.UNKNOWN, RuntimeType.STRUCT
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_head, f_tail
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 2)
			throw new IndexOutOfBoundsException("Invalid field count in Cons");
		f_head = (Object)values[0];
		f_tail = (Struct)values[1];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 13) return 13-tmp;
		Struct_Cons other = (Struct_Cons)other_gen;
		tmp = FlowRuntime.compareByValue(f_head, other.f_head);
		if (tmp != 0) return tmp;
		tmp = f_tail.compareTo(other.f_tail);
		return tmp;
	}
}
