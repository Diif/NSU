package pojo;

import java.util.Arrays;

public class Detail {
    private int id;
    private String name;
    private char symbol;
    private int symbol_count;
    private double mass;
    private double thickness;
    private double diameter;
    private double width;
    private double height;
    private double shelf_width;
    private int[] reference_id;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Detail{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", symbol=" + symbol +
                ", symbol_count=" + symbol_count +
                ", mass=" + mass +
                ", thickness=" + thickness +
                ", diameter=" + diameter +
                ", width=" + width +
                ", height=" + height +
                ", shelf_width=" + shelf_width +
                ", reference_id=" + Arrays.toString(reference_id) +
                '}';
    }

    public void setName(String name) {
        this.name = name;
    }

    public char getSymbol() {
        return symbol;
    }

    public void setSymbol(char symbol) {
        this.symbol = symbol;
    }

    public int getSymbol_count() {
        return symbol_count;
    }

    public void setSymbol_count(int symbol_count) {
        this.symbol_count = symbol_count;
    }

    public double getMass() {
        return mass;
    }

    public void setMass(double mass) {
        this.mass = mass;
    }

    public double getThickness() {
        return thickness;
    }

    public void setThickness(double thickness) {
        this.thickness = thickness;
    }

    public double getDiameter() {
        return diameter;
    }

    public void setDiameter(double diameter) {
        this.diameter = diameter;
    }

    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public double getShelf_width() {
        return shelf_width;
    }

    public void setShelf_width(double shelf_width) {
        this.shelf_width = shelf_width;
    }

    public int[] getReference_id() {
        return reference_id;
    }

    public void setReference_id(int[] reference_id) {
        this.reference_id = reference_id;
    }
}
