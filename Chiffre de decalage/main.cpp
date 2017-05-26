#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;


// Foncteur qui effectue un chiffrement par decalage
class ChiffrementDecal{

public:

  // Constructeur prenant le decalage voulu en argument
     ChiffrementDecal(int decalage, string mot_a_crypter) {
        m_decalage = decalage;
        m_mot = mot_a_crypter;
    }

    // création et initialisation de l'alpabet
  char alphabet[26] {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  //fonction qui retourne l'indice d'une lettre
    int retourner_indice_lettre(char a)
    {
       int  i = 0;

           bool trouver = false;
           while(i<25 && !trouver)
           {
               if( alphabet[i] == a)
                   trouver = true;
               i++;
           }
           if(i <= 25)
               return i;
           else
               return -1;

    }


     string operator()()
    {
         int position;
         //on parcour tous les charactères du mot
         for (float i =0; i < m_mot.size();i++)
         {
             //si le carctère est une lettre majuscule
             if(isalpha(m_mot[i]) && isupper(m_mot[i]))
             {
                 //on recupère l'indice du caractère correpondant
                 int indice = retourner_indice_lettre(m_mot[i]);

                 //on se positionne à la lettre correspondant au décalage
                 position = indice + m_decalage;

                 //pour eiter le depassement de la lettre Z
                 if(position > 26)
                 {
                     position = position % 26;
                 }

                 m_le_mot_crypter += alphabet[position-1];
              }
             else
             {
             m_le_mot_crypter += m_mot[i];
            }
         }


        return m_le_mot_crypter;

    }

  // A vous de jouer...

private:

  int m_decalage; // Le decalage a appliquer au texte
  string m_mot, m_le_mot_crypter;

};

//cette classe permet d'afficher en utlisant un itérateur
class Afficher{
public:
    void operator()(string leMot)
    {
        //declaration d'un itérateur pour parcourir la chaine
        string :: iterator it;

        for(it = leMot.begin(); it != leMot.end();it++)
            cout << *it << ",";
    }
};

int main()
{

  // Le message a crypter
  string texte("BIENVENUE SUR LE MOOC C++ D'OCR !!"), continuer("oui");
  vector <string> texte_crypter(1);
  int decalage;
    while(continuer == "oui")
     {
      do
      {

          // Demande du decalage a l'utilisateur
          cout << "Quel decalage voulez-vous utiliser ? ";
          cin >> decalage;

          //si le decalage est 0 ou 26 o, met tout à zero pour qu'il nèyait aucune modification
          if(decalage == 0 || decalage == 26)
          {
              decalage = 0;
          }

          if(decalage > 26)
            {
              decalage = decalage % 26;
          }
       }
      while(decalage < 0);

      //déclaration du foncteur qui va nous permettre
      ChiffrementDecal Decale(decalage,texte);

      // générer Chaine de caracteres pour le message crypter
      generate(texte_crypter.begin(),texte_crypter.end(),Decale);

        //afficher le message crypté avec le for each
        for_each(texte_crypter.begin(),texte_crypter.end(),Afficher());

        cout<<endl;
        cout<<"Continuer?(tapez oui ou non):";
        cin>>continuer;
    }
  return 0;
}

