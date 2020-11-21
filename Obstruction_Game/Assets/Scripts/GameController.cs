using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{

    public GameObject gridSpace;
    public int width = 128;
    public int height = 128;

    void Awake()
    {

        for (int y = 426; y >= -426; y=y-170)
        {

            for (int x = -426; x <= 426; x=x+170)
            {

                Instantiate(gridSpace, new Vector3(x, y, 0), Quaternion.identity);
            }
        }
    }

}
