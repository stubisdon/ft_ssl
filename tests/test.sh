#!/bin/sh -e

alias blue='echo -en "\033[36m"'
alias red='echo -en "\033[31m"'
alias purple='echo -en "\033[35m"'
alias default= 'echo -en "\033[0m"'
alias formatOutput='while read line; do blue; echo $line; red; done'

# supposedly, we are in a 'tests' folder, let's get outta here
# cd ..;

make;
echo "made";
echo "\n";
make re;
echo "made re";
echo "\n";
make clean;
echo "made clean";
echo "\n";
make fclean;
echo "made f*ing clean";
echo "\n";
make;
echo "made again";
echo "\n";

echo "\n";
echo "-----------------------";
echo "\n";

echo "testing openssl md5";
echo "echo "pickle rick" | openssl md5";
echo "pickle rick" | openssl md5;
echo "\n";

echo "testing pure md5";
echo "pickle rick" | md5;
echo "\n";

echo "testing ft_ssl";
echo "pickle rick" | ./ft_ssl md5;
echo "\n";

echo "-----------------------";
echo "\n";

echo "ok, now it outputs the original message and the hash on the next line";
echo "\nft_ssl: "
echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p;
echo "original md5: ";
echo "Do not pity the dead, Harry." | md5;
echo "\n";

echo "ok, now same but sha";
echo "\nft_ssl: "
echo "Do not pity the dead, Harry." | ./ft_ssl sha256 -p;
echo "original sha256: ";
echo "C9941E4521549B5BEF8A7CC4F23DD34EA7A7AAC87CBFF14F1D084E0B16B4B964";
echo "\n";

echo "-----------------------";
echo "\n";

echo "ok, now sha256 hashes from a string";
echo "\nft_ssl: "
./ft_ssl sha256 -q -s "Do not pity the dead, Harry.";
echo "original sha256: ";
echo "C9941E4521549B5BEF8A7CC4F23DD34EA7A7AAC87CBFF14F1D084E0B16B4B964";
echo "\n";

echo "-----------------------";
echo "\n";

echo "now it just outputs the hash from a message given through STDIN";
echo "Pity the living." | ./ft_ssl md5 -q -r;
echo "\n";

echo "original md5";
echo "Pity the living." | md5 -q -r;
echo "\n";

echo "-----------------------";
echo "\n";

echo "now we put a line in a file and call to md5 from a file"
echo "And above all," > file;
./ft_ssl md5 file;
echo "\n";

echo "original md5"
echo "And above all," > file;
md5 file;
echo "\n";

echo "ft_sha256 dat thing";
./ft_ssl sha256 file;
echo "\n";

echo "original sha256";
openssl sha -sha256 file;

echo "-----------------------";
echo "\n";

echo "now we call a -r(everse) flag on top of reading from a file";
./ft_ssl md5 -r file;
echo "\n";

echo "now we md5 from a string with a -s flag";
 ./ft_ssl md5 -s "pity those that aren't following baerista on spotify.";
echo "\n";

echo "\n";
echo "-----------------------";
echo "\n";

echo "we md5 with -p flag from a file and then send a string through STDIN";
echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file;
echo "\n";

echo "now, the original md5 thing";
echo "be sure to handle edge cases carefully" | md5 -p file;
echo "\n";

echo "-----------------------";
echo "\n";


echo "now we kinda show that with no -p flag there's no reading from STDIN";
echo "some of this will not make sense at first" | ./ft_ssl md5 file;
echo "\n";

echo "now we show that with -r flag it reverses hashes output, string first";
echo "but eventually you will understand" | ./ft_ssl md5 -p -r file;
echo "\n";

echo "now we show that with how -p and -s flags work with string, file and then string";
echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file;
echo "\n";

echo "I don't understand this one does";
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar";
echo "\n";

echo "aaand this one";
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar";
echo "\n";

echo "-----------------------";
echo "\n";

echo "testing sha256"
echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
./ft_ssl sha256 -q big_smoke_order_remix
echo "\n";
echo "the result should be:\n";
echo "a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9";
echo "\n";

echo "just in case, original sha256:";
openssl sha -sha256 big_smoke_order_remix;

echo "-----------------------";
echo "\n";

echo "testing ft_ssl on 'wubba lubba dub dub' from a file:";
./ft_ssl sha256 -s "wubba lubba dub dub";
echo "\n";

echo "testing ft_ssl on 'wubba lubba dub dub' from a file:";
./ft_ssl sha256 -s "wubba lubba dub dub";
echo "\n";

echo "wubba lubba dub dub" > testword;
echo "testing openssl on 'wubba lubba dub dub':";
openssl sha -sha256 testword;

echo "ok, bye. end of test";
make fclean;
rm -f file;
rm -f big_smoke_order_remix;
rm -f testword;
