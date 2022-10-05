// HASH COLLISIONS: YES
// timestamp: 1.664894312843E12

package main;

import com.area9innovation.flow.*;

public class Struct_Grammar extends Struct {
	public Object[] f_productions;

	public Struct_Grammar() {}
	public Struct_Grammar(Object[] a_productions) {
		f_productions = a_productions;
	}

	public int getTypeId() { return 20; }
	public String getTypeName() { return "Grammar"; }

	private static final String[] field_names = new String[] {
		"productions"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.ARRAY
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_productions
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Grammar");
		f_productions = (Object[])values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 20) return 20-tmp;
		Struct_Grammar other = (Struct_Grammar)other_gen;
		tmp = FlowRuntime.compareByValue(f_productions, other.f_productions);
		return tmp;
	}
}
