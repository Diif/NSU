// HASH COLLISIONS: YES
// timestamp: 1.664894312862E12

package main;

import com.area9innovation.flow.*;

public class Struct_Val extends Struct {
	public double f_val;

	public Struct_Val() {}
	public Struct_Val(double a_val) {
		f_val = a_val;
	}

	public int getTypeId() { return 110; }
	public String getTypeName() { return "Val"; }

	private static final String[] field_names = new String[] {
		"val"
	};
	private static final RuntimeType[] field_types = new RuntimeType[] {
		RuntimeType.DOUBLE
	};
	public String[] getFieldNames() { return field_names; }
	public RuntimeType[] getFieldTypes() { return field_types; }

	public Object[] getFields() {
		return new Object[] {
			f_val
		};
	}
	@SuppressWarnings("unchecked")
	public void setFields(Object[] values) {
		if (values.length != 1)
			throw new IndexOutOfBoundsException("Invalid field count in Val");
		f_val = (Double)values[0];
	}

	public int compareTo(Struct other_gen) {
		if (other_gen == this) return 0;
		int tmp = other_gen.getTypeId();
		if (tmp != 110) return 110-tmp;
		Struct_Val other = (Struct_Val)other_gen;
		if (f_val != other.f_val)
			return (f_val > other.f_val) ? 1 : -1;
		return 0;
	}
}
