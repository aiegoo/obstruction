using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GridSpace : MonoBehaviour
{

    public Button button;
    public Text buttonText;
    public string playerSymbol;

    public void buttonClick()
    {

        playerSymbol = "X";
        buttonText.text = playerSymbol;
        button.interactable = false;
    }

}
