
Building a Spam Filter in C


A while back, I recall a discussion about the practical applications of C, such as building a spam filter, which piqued my interest more than tasks like generating Fibonacci numbers. I had mentioned that I had a C program that I use for spam filtering and had offered to share it in stages. Unfortunately, there wasn't much response at the time, and I hadn't taken any further action. However, today, I found two spam messages that managed to slip through my existing filter, which has left me frustrated and motivated to update my filter program. So, I've decided to share it here to see if there's any interest.

To give you some context, my email filtering is primarily done with Procmail, and I highly recommend the Infinite Ink Procmail Quickstart for setting up Procmail if you haven't already. I use a set of Procmail rules based on a package called "spast" (Simple Procmail Anti-Spam Template), though it appears that spast is no longer available online. A basic spast rule involves setting up definitions for various phrases, like "viagra," "make money," and "free," which are stored in a file called SUBJECT_REJECTS. Any email with a subject line matching one of these phrases is filtered into my spam folder.

Now, here's where C comes into play. While this approach works well for many cases, there are situations where regular expressions and simple text matching are not sufficient. For instance, I encountered a lot of spam in Asian languages that didn't consistently use the correct character encoding in the email headers, making charset-based filtering unreliable. These messages often appeared as gibberish in my inbox, consisting of consonants and punctuation marks. To tackle this, I developed a C program to detect these types of spam messages.


#include <stdio.h>
#include <string.h>

// Define a list of spam words
const char *spamWords[] = {
    "viagra",
    "make money",
    "free",
    "credit card",
    // Add more spam words here
};

// Function to check if a word is a spam word
int isSpamWord(const char *word) {
    for (int i = 0; i < sizeof(spamWords) / sizeof(spamWords[0]); i++) {
        if (strstr(word, spamWords[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char email[1000];
    printf("Enter the email text: ");
    fgets(email, sizeof(email), stdin);

    char *word = strtok(email, " "); // Split the email into words
    int foundSpamWord = 0;

    while (word != NULL) {
        if (isSpamWord(word)) {
            foundSpamWord = 1;
            break;
        }

        word = strtok(NULL, " "); // Get the next word
    }

    if (foundSpamWord) {
        printf("The email is likely spam.\n");
    } else {
        printf("The email is likely not spam.\n");
    }

    return 0;
}



The program allows you to input an email text, and it checks for the presence of spam words within the text. It maintains a list of spam words, and if any of these words are found in the email, it categorizes the email as likely spam.

I believe this C program could be a valuable addition to a spam filtering system, especially for cases where simple text matching is insufficient. If you find it useful or have any questions or suggestions, please feel free to let me know. Your feedback is greatly appreciated. - Akkana

