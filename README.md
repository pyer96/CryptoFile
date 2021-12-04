# CryptoFile
The purpose of this project is showing and testing the possibility to realize a distributed online storage system whose security is independent from the cloud service providers.
In other words: is it possible to store data and access them in a way that they result securely stored and inaccessible, even partially, to anyone including those providers?
The answer is yes and this is where the AONT transform starts playing its crucial role as it lets us crypt (transform) a bunch of data without the necessity of storing the key used
in the process thus allowing us to manage the encrypted file independently from its key which represent a remarkable advantage over other encrypting techniques.
As a matter of fact this characteristic distinguish this “data masking” method from the other ciphers algorithms and make it so that it doesn’t belong to any encryption family 
because its key is public, stored in the data itself and therefore it doesn’t need to be traded between two communicants in order for them to share some AONT masked data. 
More precisely it is defined as an unkeyed, invertible, randomized transformation and is impossible to invert unless we get to obtain all of its output. 
As it is suggested by its name, in fact, AONT stands for All-Or-Nothing-Transform and turned out to be an essential procedure when applied before any other encryption method 
since it enhances significantly its security.

What do we mean with distributed?

We call this whole system distributed since we are going to split a single data file into a chosen number of slices and store, after being encrypted, each in a different online 
storage cloud making them available in a wider and more distributed environment that will grant more flexibility and efficiency. For the purpose of testing this technique in our
project we worked with Google Drive and Dropbox API’s ( Application Programming Interface ).
