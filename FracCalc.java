import java.util.*;

/*
 * Programmer: Sheen
 * Date: 10/18/2020
 * Purpose: Fraction Calculator project final.
 *      uses Scanner input
 *      default mode returns improper fractions, can toggle or set case by case to mixed fractions
 *          reduction funtionality
 *      order of operations
 */

public class FracCalc {
    // orig input, index current number starts at, index fraction starts at, index number ends at, parsed arraylist
    private static void parseFraction(String input, int lastEnd, int fraction, int i, ArrayList<String> parsed) {
        parsed.add(input.substring(lastEnd, lastEnd + fraction));
        parsed.add(input.substring(lastEnd + fraction + 1, i));
    }

    private static ArrayList<String> parseString(String input) {
        ArrayList<String> parsed = new ArrayList<String>();
        int lastEnd = 0;
        int atEnd = 0;
        
        for(int i = 0; i < input.length(); i++) {
            if(input.substring(i, i + 1).equals(" ") || i == input.length() - 1) {
                if(i == input.length() - 1) atEnd = 1;

                int mixed = input.substring(lastEnd, i + 1 * atEnd).indexOf("_");

                if(mixed != -1) {
                    parsed.add(input.substring(lastEnd, lastEnd + mixed));
                    parseFraction(input, lastEnd + mixed + 1, input.substring(lastEnd + mixed + 1, 
                        i + 1 * atEnd).indexOf("/"), i + 1 * atEnd, parsed); // if mixed must have fraction
                }
                
                else { // not mixed, can either have only int, sign, or fraction
                    if(input.substring(lastEnd, i + 1 * atEnd).indexOf("/") != -1) { // fraction or division
                        if(input.substring(lastEnd, i + 1 * atEnd).length() > 1) {
                            parsed.add("0");
                            parseFraction(input, lastEnd, input.substring(lastEnd, i).indexOf("/"), i + 1 * atEnd, parsed);
                        }
                        else parsed.add(input.substring(lastEnd, i + 1 * atEnd));
                    }

                    else {
                        try {
                            int signOrNum = Integer.valueOf(input.substring(lastEnd, i + 1 * atEnd));
                            parsed.add(input.substring(lastEnd, i + 1 * atEnd));
                            parsed.add("0");
                            parsed.add("1");
                        }

                        catch(Exception numberFormatException) {
                            parsed.add(input.substring(lastEnd, i + 1 * atEnd));
                        }
                    }
                }

                lastEnd = i + 1;
            }          
        }

        return parsed;
    }

    private static void convertToImpropers(ArrayList<String> parsed) {
        for(int i = 0; i < parsed.size(); i += 4) {
            int numerator = Integer.parseInt(parsed.get(i + 1));
            int wholeToFrac = Integer.parseInt(parsed.get(i)) * Integer.parseInt(parsed.get(i + 2));

            if(wholeToFrac < 0) parsed.set(i + 1, Integer.toString(-1 * numerator + wholeToFrac));
            else parsed.set(i + 1, Integer.toString(numerator + wholeToFrac));

            parsed.set(i, "0");
        }

        // System.out.println(parsed);
    }

    private static int fixOrder(int i, ArrayList<String> parsed, String answer) {
        parsed.set(i + 2, answer.substring(0, answer.indexOf("/")));
        parsed.set(i + 3, answer.substring(answer.indexOf("/") + 1));

        for(int j = 0; j < 4; j++) parsed.remove(i - 3);

        return i - 4;
    }

    private static String addSubtract(int start, ArrayList<String> parsed, int addSubtract) {
        int numer1 = Integer.parseInt(parsed.get(start));
        int denom1 = Integer.parseInt(parsed.get(start + 1));
        int numer2 = Integer.parseInt(parsed.get(start + 4));
        int denom2 = Integer.parseInt(parsed.get(start + 5));
        
        if(denom1 == denom2) return Integer.toString(numer1 + addSubtract * numer2) + "/" + Integer.toString(denom1);
        else return Integer.toString(numer1 * denom2 + addSubtract * numer2 * denom1) + "/" + Integer.toString(denom1 * denom2);
    }

    private static String multDiv(int start, ArrayList<String> parsed, int multDiv) {
        int numer1 = Integer.parseInt(parsed.get(start));
        int denom1 = Integer.parseInt(parsed.get(start + 1));
        int numer2 = Integer.parseInt(parsed.get(start + 4));
        int denom2 = Integer.parseInt(parsed.get(start + 5));

        if(multDiv == 1) return Integer.toString(numer1 * numer2) + "/" + Integer.toString(denom1 * denom2);
        else return Integer.toString(numer1 * denom2) + "/" + Integer.toString(numer2 * denom1);
    }

    private static int gcd(int a, int b) {
        int gcd = 1;

        for(int i = Math.max(a, b); i >= 2 ; i--) {
            if(a % i == 0 && b % i == 0) {
                gcd = i;
                i = 0;
            }
        }

        return gcd;
    }

    private static String reduce(String answer) { // also catches 0s
        int fraction = answer.indexOf("/");
        int numerator = Integer.parseInt(answer.substring(0, fraction));
        int denominator = Integer.parseInt(answer.substring(fraction + 1));

        if(numerator == 0) return "0";
        else {
            int gcd = gcd(numerator, denominator);
            int reducednumer = numerator / gcd;
            int reduceddenom = denominator / gcd;

            if(reduceddenom == 1) return Integer.toString(reducednumer);
            else return Integer.toString(reducednumer) + "/" + Integer.toString(reduceddenom);
        }
    }

    private static String convertToProper(String answer) {
        int improperFraction = answer.indexOf("/");
        
        if(improperFraction != -1) {
            int denominator = Integer.parseInt(answer.substring(improperFraction + 1));
            String whole = Integer.toString(Integer.parseInt(answer.substring(0, improperFraction)) / denominator);
            String numerator = Integer.toString(Integer.parseInt(answer.substring(0, improperFraction)) % denominator);

            if(whole.equals("0")) return numerator + "/" + denominator;
            else return whole + "_" + numerator + "/" + denominator;
        }

        return answer;
    }

    public static String produceAnswer(String input, String mode) {
        ArrayList<String> parsed = parseString(input);
        convertToImpropers(parsed);
        String answer = "";

        for(int i = 3; i < parsed.size(); i += 4) {
            if(parsed.get(i).equals("*")) {
                answer = multDiv(i - 2, parsed, 1);
                i = fixOrder(i, parsed, answer);
            }

            else if(parsed.get(i).equals("/")) {
                answer = multDiv(i - 2, parsed, -1);
                i = fixOrder(i, parsed, answer);
            }
        }

        for(int i = 3; i < parsed.size(); i += 4) {
            if(parsed.get(i).equals("+")) {
                answer = addSubtract(i - 2, parsed, 1);
                i = fixOrder(i, parsed, answer);
            }
    
            else if(parsed.get(i).equals("-")) {
                answer = addSubtract(i - 2, parsed, -1);
                i = fixOrder(i, parsed, answer);
            }
        }

        answer = reduce(answer);
        if(mode.equals("mixed")) answer = convertToProper(answer);

        return answer;
    }

    public static void help() {
        System.out.println("Usage:");
        System.out.println("    Expressions: <operand> <operator> <operand> ...");
        System.out.println("        mixed fraction syntax: <whole>_<numerator>/<denominator>");
        System.out.println("        fraction syntax: <numerator>/<denominator>");
        System.out.println("    Answer Mode: default automatically set to improper (and whole numbers)");
        System.out.println("        to change mode: default = <mixed/improper>");
        System.out.println("        line by line: <mixed/improper> <expression>");
        System.out.println("    Exiting: power off");
        System.out.println("    Help: help");
    }

    public static void main(String args[]) {
        help();

        Scanner in = new Scanner(System.in);
        String input = "";
        String mode = "improper";
        boolean off = false;
        
        while(!off) {
            input = in.nextLine();

            if(input.equals("power off")) off = true;
            else if(input.equals("help")) help();
            else if(input.length() > 15 && input.substring(0, 10).equals("default = ")) {
                String changeMode = input.substring(10);
                if (changeMode.equals("improper")) mode = "improper";
                else if(changeMode.equals("mixed")) mode = "mixed";
                else System.out.println("only two modes possible: mixed and improper");
            }

            else {
                try {
                    int modeOrExpression = Integer.valueOf(input.substring(0, 1));
                    System.out.println(produceAnswer(input, mode));
                }

                catch(Exception numberFormatException) {
                    int i = 0;
                    while(!input.substring(i, i + 1).equals(" ") && i < input.length() - 1) i++;
                    
                    String caseMode = input.substring(0, i);
                    if(i == input.length() - 1) help();
                    else if (caseMode.equals("improper")) System.out.println(produceAnswer(input.substring(i + 1), caseMode));
                    else if(caseMode.equals("mixed")) System.out.println(produceAnswer(input.substring(i + 1), caseMode));
                    else System.out.println("usage: <optional mode: mixed/improper> <expression>; no " + caseMode + " mode");
                }
            }
        }

        /* sample test cases:
        *  System.out.println(FracCalc.produceAnswer("12/3 / 6/3")); // 36/18
        *  System.out.println(FracCalc.produceAnswer("1/4 + 1_1/2")); // 1_3/4
        *  System.out.println(FracCalc.produceAnswer("8/4 + 2")); // 4
        *  System.out.println(FracCalc.produceAnswer("-1 * -1/2")); // 1/2
        *  System.out.println(FracCalc.produceAnswer("3 + -1 * -1/2")); // 3_1/2
        *  System.out.println(FracCalc.produceAnswer("-11/17 -1/17")); // -12/17
        *  System.out.println(FracCalc.produceAnswer("0 * 25_462/453")); // 0
        *  System.out.println(FracCalc.produceAnswer("5_3/4 - 6_5/8")); // -7/8 
        *  System.out.println(FracCalc.produceAnswer("-3/7 - 20")); // -143/7 
        *  System.out.println(FracCalc.produceAnswer("-32 - 27/21")); // -699/21 = -233/7 

        * System.out.println(FracCalc.produceAnswer("1 + 2 + 3")); // 6
        * System.out.println(FracCalc.produceAnswer("3/4 * 4")); // 3
        * System.out.println(FracCalc.produceAnswer("-1/2 * 4 + 3/4")); // -1_1/4
        * System.out.println(FracCalc.produceAnswer("5_3/4 - -6_8/8 - 5_3/4")); // 7 */
    }
}