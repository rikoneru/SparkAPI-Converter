import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.File;

/**
 * This is the main class for the Scanner
 */

/**
 * @author Danny Reinheimer
 *
 */
public class Scanner {

	/**
	 * @param args The file name 
	 */
	public static void main(String[] args) {
		// checks to see if we are given any arguments
		if(args.length < 1) {
			System.err.println("Please provide an input file to process");
			System.exit(1);
		}
		
		String fileName = args[0];
		Scan scan2 = new Scan(fileName);
		Pair<TokenNames,String> tokenPair;
		
		try {
			// get the name of the file minus the dot 
			int pos = fileName.lastIndexOf(".");
			String newFileName = fileName.substring(0, pos) + "_gen.scala";
			PrintWriter writer = new PrintWriter(newFileName,"UTF-8");

			int sign = 0;
			// keep getting the next token until we get a null

			String newFileName2 = "input_nospace.scala";
			PrintWriter writer2 = new PrintWriter(newFileName2,"UTF-8");

			while((tokenPair = scan2.getNextToken()) != null) {
				if((tokenPair.getKey() == TokenNames.Identifiers) || (tokenPair.getKey() == TokenNames.Numbers) 
					|| (tokenPair.getKey() == TokenNames.Symbol) || (tokenPair.getKey() == TokenNames.String)){
					writer2.print(tokenPair.getValue());
			    }
			}

	        writer2.close();

			Scan scan = new Scan(newFileName2);

			while((tokenPair = scan.getNextToken()) != null) {
				boolean mark = false;
				
				   // System.out.println(tokenPair.getKey() + " :" + tokenPair.getValue());
				
				// if (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().contains(".")) System.out.println("!!!!!!!!!!");
				
			//	writer.print(tokenPair.getKey() + ": " + tokenPair.getValue() + "\n");

				//tranform rules
				if(tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("sc")) {
					String newName = "spark";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("range")) {
					String newName = "range";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("textFile")) {
					String newName = "read.textFile";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("map")) {
					String newName = "map";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("filter")) {
					String newName = "filter";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("collect")) {
					String newName = "collect";
					writer.print(newName);
					mark = true;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("reduce")) {
					String newName = "select(reduceAggregator";
					writer.print(newName);
					mark = true;
					sign = 1;
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("reduceByKey")) {
					String newName = "groupByKey(_._1).agg(reduceByKeyAggregator";
					writer.print(newName);
					mark = true;
					sign = 2;
					// System.out.println("!!");
				}

				if (tokenPair.getKey() == TokenNames.Identifiers && tokenPair.getValue().equals("sortBy")) {
					String newName = "map(row=>(";
					writer.print(newName);
					mark = true;
					sign = 3;
				}


                if (sign == 1 && (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")"))){
					sign = 10;
					writer.print(tokenPair.getValue());
					continue;
				}
				if (sign == 2 && (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")"))){
					sign = 20;
					writer.print(tokenPair.getValue());
					continue;
				}
				if (sign == 3 && (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")"))){
					// System.out.println("!!");
					sign = 30;
					writer.print(tokenPair.getValue());
					continue;
			    }
				
					if (sign == 10){
						if (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(".")){
						String newName = ").collect().";
						writer.print(newName);
						mark = true;
						sign = 0;
					    }
					    else{
					    	if (!(tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")")))
					    	sign = 1;
					    }
					}
					if (sign == 20){
						if (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(".")){
						String newName = ").";
						writer.print(newName);
						mark = true;
						sign = 0;
					    }
						else{
							if (!(tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")")))
					    	sign = 2;
					    }

					}
					if (sign == 30){
						// System.out.println("??");
					   if (tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(".")){
						String newName = "(row), row)).orderBy(\"_1\").map(_._2).";
						writer.print(newName);
						mark = true;
						sign = 0;
					   }
					   else{
					   	if (!(tokenPair.getKey() == TokenNames.Symbol && tokenPair.getValue().equals(")")))
					   	   sign = 3;
					   }

					}

					// else{
					    // just add it to the output with out modifying the values
				if (mark == false){
						writer.print(tokenPair.getValue());
					// }
					}
				}

				if (sign == 10){
						String newName = ").collect()";
						writer.print(newName);
					}
					if (sign == 20){
						String newName = ")";
						writer.print(newName);

					}
					if (sign == 30){ 
						String newName = "(row), row)).orderBy(\"_1\").map(_._2)";
						writer.print(newName);
					}
		
				

			writer.close();
			File file = new File("input_nospace.scala");
			file.delete();
		} catch (FileNotFoundException e) {
			System.err.println("Could not create output file");
			System.exit(1);
		} catch (UnsupportedEncodingException e) {
			System.err.println("Error encoding output file.  Not my fault though");
			System.exit(1);
		}
		
		
		

	}

}