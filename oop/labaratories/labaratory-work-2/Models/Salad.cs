namespace labaratory_work_2.Models
{
    public enum Dressing
    {
        OliveOil,
        Mayonnaise
    }

    public class Salad(string name, int weight, double price)
        : Dish(name, weight, price)
    {
        public Dressing Dressing { get; private set; } = Dressing.OliveOil;

        public void ChangeDressing()
        {
            Dressing = Dressing == Dressing.OliveOil ? Dressing.Mayonnaise : Dressing.OliveOil;
        }

        public void TossWithDressing()
        {
            Console.WriteLine($"Tossing the salad with {Dressing}");
        }

        public override void DisplayInfo()
        {
            Console.WriteLine($"Salad: {Name}, {Dressing} dressing, {Weight}g, ${Price:F2}, ");
        }

        public override double GetFullPrice()
        {
            return Dressing == Dressing.OliveOil ? Price * 1.4 : Price * 1.3;
        }
    }
}
