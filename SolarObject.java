
//author xiao wang at stevens cwid:10427141
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class SolarObject {
	String name;
	double mass;
	double diameter;
	String orbits;
	double meanDis;

	SolarObject(String name, double mass, double diameter, String orbits, double meanDis) {
		this.name = name;
		this.mass = mass;
		this.diameter = diameter;
		this.orbits = orbits;
		this.meanDis = meanDis;
	}

	public static void main(String argus[]) {
		String[] names = { "Sun", "Venus", "Earth", "Moon" };
		ArrayList<SolarObject> sos = new ArrayList<SolarObject>();

		String dat = "";
		try {
			dat = new String(Files.readAllBytes(Paths.get("solarsystem.dat")), "UTF-8");
		} catch (Exception e) {
		}
		String[] objects = dat.split("\n");

		for (String object : objects) {
			String[] items = object.split("\\s+");
			for (String name : names) {
				if (name.equals(items[0])) {
					double mass = Double.parseDouble(items[2]);
					double diameter = Double.parseDouble(items[3]);
					String orbits = items[1];
					double meanDis = (Double.parseDouble(items[4]) + Double.parseDouble(items[5])) / 2;
					SolarObject so = new SolarObject(name, mass, diameter, orbits, meanDis);
					sos.add(so);
				}
			}
		}
		
		System.out.println("name   "+"mass    "+"diameter    "+"orbits    "+"meanDis");
		for(SolarObject so:sos) {
			System.out.println(so.name+"   "+so.mass+"    "+so.diameter+"    "+so.orbits+"    "+so.meanDis);
		}

	}
}
