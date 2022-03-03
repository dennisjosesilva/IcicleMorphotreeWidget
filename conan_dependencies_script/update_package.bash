conan remove morphotree/0.0.1@dennisjosesilva/dev --force;  
echo ""
echo "Package morphotree has been removed.";  
echo "======================================================================================";
conan create ./morphotree morphotree/0.0.1@dennisjosesilva/dev;

echo "";
echo "======================================================================================";
echo "Package morphotree has been created again with the updated code.";