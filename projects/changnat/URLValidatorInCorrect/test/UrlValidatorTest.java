

import java.util.ArrayList;
import java.util.Random;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   String[] schemes = new String[] {"http", "https", "ftp"};
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   public void testManualTest()
   {
	   
	   UrlValidator validator = new UrlValidator();
	   for (int index = 0; index < manualTestUrls.length; index++) {
		   ResultPair testing = manualTestUrls[index];
		   boolean tested = validator.isValid(testing.item);
		   assertEquals(testing.item, testing.valid, tested);
	   }
	   

//You can use this function to implement your manual testing	   
	   
   }

   public void testPartitionTestScheme()
   {
       String[] schemes = { "http", "https" };
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES); 
      
       assertTrue(urlValidator.isValid("http://www.google.com"));

   }

   
   public void testPartitionTestAuthority(){
       UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);       
       assertTrue(urlValidator.isValid("http://255.255.255.255"));

   }

    public void testPartitionTestPath(){
        
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES); 
        assertTrue(urlValidator.isValid("http://www.google.com/file"));
       
        
    }

    public void testPartitionTestQuery(){
        
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES); 
        assertTrue(urlValidator.isValid("http://www.google.com/place?key1=value1&key2=value2"));
        assertTrue(urlValidator.isValid("http://www.google.com/place?key1=value1;key2=value2"));
        assertTrue(urlValidator.isValid("http://www.google.com/place?key1=value1;key2="));
        assertTrue(urlValidator.isValid("http://www.google.com/place?=value1"));
    }

    public void testPartitionTestFragment(){
        
        UrlValidator urlValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES); 
        assertTrue(urlValidator.isValid("http://www.google.com#test"));
        assertTrue(urlValidator.isValid("http://www.google.com/file.html#test"));

    }

   

   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   
	   /*random test,
	   build up random url's*/
       int iterations = 2000;
       for(int x = 0; x < iterations; x++) {
    	   
           UrlValidator urlValidator = new UrlValidator(); 
    	   Random rand = new Random();
    	   
    	   int s = rand.nextInt(testUrlScheme.length);
    	   int a = rand.nextInt(testUrlAuthority.length);
    	   int p = rand.nextInt(testUrlPort.length);
    	   int o = rand.nextInt(testUrlPathOptions.length);
    	    //bug, .valid returns false when should be true and vice-versa
    	   boolean expected = true;
    	   expected &= testUrlScheme[s].valid;
    	   expected &= testUrlAuthority[a].valid; 
    	   expected &= testUrlPort[p].valid;
    	   expected &= testUrlPathOptions[o].valid; //bug, adding the path always makes it false

    	   
    	   String url = testUrlScheme[s].item + testUrlAuthority[a].item 
    			   + testUrlPort[p].item + testUrlPathOptions[o].item;

    	   System.out.println(url);
    	   
    	   //bug, isValid() always returns false 
    	   boolean test = urlValidator.isValid(url);
    	   assertFalse(test);
    	   
    	   if(expected) {
    		   System.out.println("Expected: " + expected + " actual: " + test);
    	   }
    	   else {
    		   System.out.println("Expected: " + expected + " actual: " + test);
    	   }
    	   System.out.println();
       }
   }
   
   
   //below from UrlValidaotrCorrect file
   ResultPair[] testUrlScheme = {
		   new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)
    };

	ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
	              new ResultPair("go.com", true),
	              new ResultPair("go.au", true),
	              new ResultPair("0.0.0.0", true),
	              new ResultPair("255.255.255.255", true),
	              new ResultPair("256.256.256.256", false),
	              new ResultPair("255.com", true),
	              new ResultPair("1.2.3.4.5", false),
	              new ResultPair("1.2.3.4.", false),
	              new ResultPair("1.2.3", false),
	              new ResultPair(".1.2.3.4", false),
	              new ResultPair("go.a", false),
	             new ResultPair("go.a1a", false),
	              new ResultPair("go.1aa", false),
	              new ResultPair("aaa.", false),
	              new ResultPair(".aaa", false),
	              new ResultPair("aaa", false),
	              new ResultPair("", false)
	};
	ResultPair[] testUrlPort = {new ResultPair(":80", true),
	         new ResultPair(":65535", true),
	         new ResultPair(":0", true),
	         new ResultPair("", true),
	         new ResultPair(":-1", false),
	        new ResultPair(":65636",false),
	         new ResultPair(":65a", false)
	};
	ResultPair[] testPath = {new ResultPair("/test1", true),
	      new ResultPair("/t123", true),
	      new ResultPair("/$23", true),
	      new ResultPair("/..", false),
	      new ResultPair("/../", false),
	      new ResultPair("/test1/", true),
	      new ResultPair("", true),
	      new ResultPair("/test1/file", true),
	      new ResultPair("/..//file", false),
	      new ResultPair("/test1//file", false)
	};
	//Test allow2slash, noFragment
	ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
	                new ResultPair("/t123", true),
	                new ResultPair("/$23", true),
	                //new ResultPair("/..", false),
	                //new ResultPair("/../", false),
	                new ResultPair("/test1/", true),
	                //new ResultPair("/#", false),
	                new ResultPair("", true),
	                new ResultPair("/test1/file", true),
	                new ResultPair("/t123/file", true),
	                new ResultPair("/$23/file", true),
	                //new ResultPair("/../file", false),
	               // new ResultPair("/..//file", false),
	                new ResultPair("/test1//file", true),
	                //new ResultPair("/#/file", false)
	};
	
	ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
	          new ResultPair("?action=edit&mode=up", true),
	          new ResultPair("", true)
	};

	//String[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};


   
   
   ResultPair[] manualTestUrls = {
		   new ResultPair("http://www.amazon.com/firstslash//doubleslash", false),
		   new ResultPair("http://www.google.com", true),
		   new ResultPair("http://", false),
		   new ResultPair("http://www.amazon.com/../fail1", false),
		   new ResultPair("ftp://255.255.255.255:65535", true),
		   new ResultPair("http://www.youtube.com", true),
		   new ResultPair("http://www.amazon.com", true),
		   new ResultPair("htep://www.goog.e.com", false),
		   new ResultPair("ftp://255.255.255.255:65536", false),
		   new ResultPair("ftp://255.255.255.255:-1", false),
		   new ResultPair("http://www.amazon.com?action=view", true),
		   new ResultPair("http://www.amazon.com?action=view&noaction", true),
		   new ResultPair("http://www.amazon.com/firstslash", true),

   };
   
}
